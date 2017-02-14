#include "SkyDome.h"

const char shaderSource[] =
{
	"#V"
	"void main() {"
	" gl_Position = ftransform();"
	" gl_TexCoord[0].st = gl_MultiTexCoord0.st;"
	"}"

	"#F"
	"uniform sampler2D texDay;"
	"uniform sampler2D texNight;"
	"uniform float time;"
	"void main() {"
	" vec4 td = texture2D(texDay, gl_TexCoord[0].st);"
	" vec4 tn = texture2D(texNight, gl_TexCoord[0].st);"
	" vec4 ret = td;"
	" if (time>20.0) ret = tn;"
/*	" if(time=>20.0 && time<6.0)"
	"  ret = td*(1-max(1.0, time)) + tn*max(1.0, time);"
	" if(time>=6.0 && time<20.0) "
	"  ret = tn*(1-max(1.0, time)) + td*max(1.0, time);"*/
	" gl_FragColor = ret;"
	"}"
};

crSkyDome::crSkyDome( void ) {
	inited = false;
}

crSkyDome::crSkyDome( crSkyParams_t params ) {
	Create(params);
}

crSkyDome::~crSkyDome( void ) {
	Destroy();
}

bool crSkyDome::Create( crSkyParams_t params ) {
	this->params = params;
	currTime = params.fDaytime;
	inited = true;

	float	theta = 2.0f*PI / (float)params.uiSides, 
			phi	   = PI/2.0f / (float)params.uiSlices;

	for (unsigned int sl=0; sl<=params.uiSlices; sl++) {
		for (unsigned int si=0; si<=params.uiSides; si++) {

			float x = cosf((sl+0.79f)*phi)   * cosf(si*theta);
			float z = sinf(si*theta) * cosf((sl+0.79f)*phi);
			vertices.Append(crVec3 (	x * params.fRadius,
										sinf(sl * phi) * params.fDampFactor  * params.fRadius,
										z * params.fRadius) + params.vPosition);

			float u,v;
			v = acosf( z ) / PI;
			u = acosf( x / (sinf(acosf(z)))) / (PI/2.f);
			texCoords.Append( crVec2(u, v));
		} 
	}

	for (unsigned int sl=1; sl<=params.uiSlices; sl++) {
		for (unsigned int si=0; si<=params.uiSides; si++) {
			indices.Append( sl     * (params.uiSides+1) + si );
			indices.Append( (sl-1) * (params.uiSides+1) + si );
		}
	}

	if (params.texNight.TexFile) {
		this->params.texNight.Id = LoadDDSTexture( params.texNight.TexFile );
	}

	if (params.texDay.TexFile) {
		this->params.texDay.Id = LoadDDSTexture( params.texDay.TexFile );
	}

	Shader.LoadFromSource((char*) shaderSource);

	
	glGenBuffers(3, &idVBO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, idVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*vertices.Count, vertices.Ptr(), GL_STATIC_DRAW);
	vertices.Free();

	glBindBuffer(GL_ARRAY_BUFFER, idVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*texCoords.Count, texCoords.Ptr(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	texCoords.Free();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idVBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indices.Count, indices.Ptr(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	indices.Free();

	return inited;
}

void crSkyDome::Destroy( void ) {
	if(!inited) return;
	glDeleteBuffers(3, &idVBO[0]);
}

void crSkyDome::Render( float time ) {
	if(!inited) return;
	
	if (time > 24.f) time -=24.f;
	currTime = time * 0.1f;

	Shader.Activate();

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[1]);
	glTexCoordPointer(2, GL_FLOAT, 0, (char*)NULL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, params.texDay.Id);
	Shader.Uniform1i("texDay", 0);


	glClientActiveTexture(GL_TEXTURE1);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[1]);
	glTexCoordPointer(2, GL_FLOAT, 0, (char*)NULL);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, params.texNight.Id);

	Shader.Uniform1i("texNight", 1);
	

	Shader.Uniform1f("time", currTime);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[0]);
	glVertexPointer(3, GL_FLOAT, 0, (char*)NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idVBO[2]);
	for (unsigned int i=0; i<params.uiSlices; i++)
		glDrawElements	(GL_TRIANGLE_STRIP, 
						(params.uiSides+1)*2, 
						GL_UNSIGNED_SHORT, 
						((char*)NULL + ((params.uiSides+1)*2*i*sizeof(unsigned short))));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);

	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glClientActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	Shader.Deactivate();
}

crVec3 crSkyDome::GetSunPosition( void ) {
	crVec3 sunPos = crVec3(params.fRadius, 0.f, 0.f);
	crQuaternion quat;
	crMat4 mat;

	quat.CreateFromEulerAngles(0.f, 0.f, -15.f * currTime );
	quat.CreateMatrix(mat.ToFloatPtr());

	return mat.ToMat3() * sunPos;
}