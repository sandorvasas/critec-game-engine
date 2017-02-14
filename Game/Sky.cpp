#include "Sky.h"

crSkyDome::crSkyDome( void ) {
	Destroy();
}

crSkyDome::~crSkyDome( void ) {
	Destroy();
}

void crSkyDome::Create(float size,  float sFactor, unsigned int Sides, unsigned int Slices, unsigned int SkyTexture, unsigned int NightTexture) {
	Destroy();
	this->SkyTexture   = SkyTexture;
	this->NightTexture = NightTexture;
	this->Sides        = Sides;
	this->Slices       = Slices;


		float xzAngle, yAngle;

		for(unsigned int i=0; i<= Slices; i++)
		{
			xzAngle = (PI/4.0f / Slices) * i;

			for(unsigned int j=0; j<= Sides; j++) {
				yAngle = (2.0f * PI / Sides) * j;

				aVertex.Append( crVec3(cosf(yAngle)  * cosf(xzAngle+ 0.79f),
								  	   sinf(xzAngle) * sFactor,
									   sinf(yAngle)  * cosf(xzAngle+ 0.79f) ) * size );
				float u,v;

		//		u = ( arccos(x/(r sin(v pi))) ) / (2 pi)

				v = acosf(   sinf(yAngle) * cosf(xzAngle)    ) / PI;
				u = (acosf(  cosf(yAngle) * sinf(xzAngle)/(sinf(v*PI)))) / (2.f*PI);
				aTexCoord.Append( crVec2( v, u ) ) ;
			}
		}
	
		for(unsigned int i=1; i<= Slices; i++)
			for(unsigned int j=0; j<= Sides; j++) {
				aIndex.Append(  i * (Sides+1) + j );
				aIndex.Append( (i-1) * (Sides+1)+ j );
			}

/*	Shader.LoadFragmentShaderFromSource(shadFragment_source);
	Shader.LoadVertexShaderFromSource(shadVertex_source);
	Shader.Link();*/
}

void crSkyDome::Render( float dayTime ) {

	glPushMatrix();
	glTranslatefv(Position.ToFloatPtr());

	/*Shader.Activate();
	glUniform1f(Shader.UniformLoc("Time"), dayTime);*/

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 8, aTexCoord.Ptr());


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, SkyTexture);
	glUniform1i(Shader.UniformLoc("SkyTexture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NightTexture);
	glUniform1i(Shader.UniformLoc("NightTexture"), 1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 12, aVertex.Ptr());

	int light  = glIsEnabled(GL_LIGHTING),
		 fog   = glIsEnabled(GL_FOG);
	
	glDisable(GL_FOG);
	glDisable(GL_LIGHTING);

	for(unsigned int i=0; i<Slices; i++)
		glDrawElements(GL_TRIANGLE_STRIP, (Sides+1)*2, GL_UNSIGNED_SHORT, &(aIndex.Ptr())[i * (Sides+1)*2] );

	if(fog)glEnable(GL_FOG);
	if(light)glEnable(GL_LIGHTING);

	glDisableClientState(GL_VERTEX_ARRAY);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

/*	glClientActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
*/
	//Shader.Deactivate();

	glPopMatrix();
}

void crSkyDome::Destroy( void ) {
	aVertex.Free();
	aIndex.Free();
	aTexCoord.Free();
	SkyTexture		 = NULL;
}