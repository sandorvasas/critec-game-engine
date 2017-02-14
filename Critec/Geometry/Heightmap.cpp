#include "Heightmap.h"
#include "../Renderer/GL/GLexp.h"
#include "../Renderer/Texture.h"

#define VBOBUFFER_OFFSET(offs) (char*)NULL + offs

const char ShaderSource[] = {

	"ßF"
	"uniform sampler2D tex0;"
	"uniform sampler2D normalmap;"

	"varying vec3 lightDir;"
	"varying vec3 viewDir;"
	
	"void main( void ) {"
	"	lightDir = normalize(lightDir);"
	"	viewDir  = normalize( viewDir);"

	"	float pH = texture2D(normalmap, gl_TexCoord[0].st).w * 0.04 - 0.02;"

	"	vec2 newTC = gl_TexCoord[0].st + (pH * -viewDir.yx) * texture2D(normalmap, gl_TexCoord[0].st).z;"

	"	vec3 normal = texture2D(normalmap, newTC).xyz * 4.0 - 2.0;"
	
	//"	float specular = clamp( dot(normal, normalize(-viewDir + lightDir)), 0.0, 1.0);"
//	"	specular = pow(specular, 16.0);"
	"	float diffuse  = clamp( dot(normal, lightDir), 0.0, 1.0 );"

	"	gl_FragColor  = diffuse * texture2D(tex0, newTC);"
	"}"

	"ßV"
	"uniform vec3 lightPos;"
	"uniform vec3 viewPos;"

	"attribute vec3 tangent;"	
	
	"varying vec3 lightDir;"
	"varying vec3 viewDir;"
	
	"void main( void ) {"
	"	gl_Position = ftransform();"
	"	gl_TexCoord[0].st = gl_MultiTexCoord0.st;"

	"	vec3 lightDIR = lightPos - gl_Vertex.xyz;"
	"	vec3 viewDIR  = viewPos - gl_Vertex.xyz;"
	"	vec3 bitangent = cross(gl_Normal, tangent);"

	"	lightDir.x = dot( tangent, lightDIR );"
	"	lightDir.y = dot( bitangent, lightDIR );"
	"	lightDir.z = dot( gl_Normal, lightDIR );"

	"	viewDir.x = dot ( tangent, viewDIR );"
	"	viewDir.y = dot ( bitangent, viewDIR );"
	"	viewDir.z = dot ( gl_Normal, viewDIR );"

	"}"
};

crHeightmap::crHeightmap( void ) {
	max = min = crVec3(0, 0, 0);
	//lightPos = crVec3(-1000.0f, 2000.0f, 1000.0f);
	lightPos = crVec3(0.0f, 10.0f, 0.f);
	heightLoaded = false;
}

crHeightmap::~crHeightmap( void ) {
	heightData.Free();
	vertices.Free();
	indices.Free();
	glDeleteBuffers(2, &IdVBO[0]);
}

bool crHeightmap::CreateGeometry( crHeightmapParams_t hp ) {
	this->hp = hp;
	Shader.LoadFromSource((char*)ShaderSource);
	
	hasTexture = (hp.tBase.s > 0.f && hp.tBase.t > 0.f );
	hasNormalmap = (hp.tNormal.s > 0.f  && hp.tNormal.t > 0.f );
	hasDetailTex = (hp.tDetail.s > 0.f  && hp.tDetail.t > 0.f );

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	crRestoreFile	 file; 
	unsigned char    rgb[3];
	if(!file.Open((const char*)hp.fileName)) return false;
	
	file.Read(&bmfh, sizeof(BITMAPFILEHEADER));
	file.Read(&bmih, sizeof(BITMAPINFOHEADER));

	file.Seek(bmfh.bfOffBits, SEEK_SET);
	
	width = bmih.biWidth;
	height = bmih.biHeight;

	int vertCount = height * width;
	heightData.Allocate( vertCount );
	vertices.Allocate( vertCount );
	indices.Allocate( vertCount*2 );

	if (hasTexture ) {
			texId[0] = LoadDDSTexture(hp.tBase.fileName);
	}

	if (hasNormalmap) {
			texId[1] = LoadDDSTexture(hp.tNormal.fileName);
	}

	if (hasDetailTex) {
			texId[2] = LoadDDSTexture(hp.tDetail.fileName);
	}

	min	   = crVec3( -width/2 * hp.vScale.x + hp.vOffset.x, 
					 0.f,
					 -height/2 * hp.vScale.y + hp.vOffset.z );

	int i = 0, curr;
	for (int h=0; h<height; h++) {
		for (int w=0; w<width; w++) {
			file.Read(&rgb, 3);
			
			curr = h*width+w;
			heightData.Ptr()[curr] = (float(rgb[0] + rgb[1] + rgb[2]) / 32.0f) * hp.vScale.y + hp.vOffset.y;

			vertices.Ptr()[curr].xyz = crVec3(		w * hp.vScale.x + min.x, 
													heightData.Ptr()[curr], 
													h * hp.vScale.x + min.z);

			if (hasTexture) {
				vertices.Ptr()[curr].st = crVec2( w*(hp.tBase.s/width), h*( hp.tBase.t/height) );
			}

			if (hasNormalmap) 
				vertices.Ptr()[curr]._st[0] = crVec2( w*(hp.tNormal.s/width), h*(hp.tNormal.t/height) );

			if (hasDetailTex) 
				vertices.Ptr()[curr]._st[1] = crVec2( w*(hp.tDetail.s/width), h*(hp.tDetail.t/height) );


			indices.Ptr()[i++] = ( (h<height-1)? h+1 : h) * width + ( (w<width-1)? w+1 : w);
			indices.Ptr()[i++] = h * width + ( (w<width-1)? w+1 : w);
		}
	}
	max = vertices.Ptr()[vertices.Count-1].xyz;

	file.Close();

	CalculateNormals();

	glGenBuffers(2, &IdVBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, IdVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crVertex)*vertices.Count, 	vertices.Ptr(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	vertices.Free();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IdVBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indices.Count, indices.Ptr(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	indices.Free();

	heightLoaded = true;
	return true;
}

void crHeightmap::CalculateNormals( void ) {
	crVec3 p[7], v[6], N;
	int c, all = height * width;

	for (int h=0; h<height; h++) {
		for(int w=0; w<width; w++) {
			c = h*width+w;
			int i[7];
			
			i[0] = c;
			i[1] = clamp( (h+1) * width + w,   0, all-1 );
			i[2] = clamp( (h+1) * width + w-1, 0, all-1 );
			i[3] = clamp( c-1,				   0, all-1 );
			i[4] = clamp( (h-1) * width + w,   0, all-1 );
			i[5] = clamp( (h-1) * width + w+1, 0, all-1 );
			i[6] = clamp( c+1,				   0, all-1 );

			for (int g=0; g<7; g++)
				p[g] = vertices.Ptr()[i[g]].xyz; 
			
			N  =  cross( p[1]-p[0], p[2]-p[0] );
			N +=  cross( p[2]-p[0], p[3]-p[0] );
			N +=  cross( p[3]-p[0], p[4]-p[0] );
			N +=  cross( p[4]-p[0], p[5]-p[0] );
			N +=  cross( p[5]-p[0], p[6]-p[0] );
			N +=  cross( p[6]-p[0], p[1]-p[0] );
			vertices.Ptr()[c].normal = normalize( N );

			if(w+h>3 && dot(vertices.Ptr()[c].normal, vertices.Ptr()[2].normal) < 0)
				vertices.Ptr()[c].normal.y = -vertices.Ptr()[c].normal.y;

			if(hasTexture) {
				/*vertices.Ptr()[c].tangent = 
					CalculateTangentVector( p[0], p[1], p[2], 
											vertices.Ptr()[i[0]].st, 
											vertices.Ptr()[i[1]].st, 
											vertices.Ptr()[i[2]].st);
*/
				vertices.Ptr()[c].CalculateTangent( vertices.Ptr()[i[0]], vertices.Ptr()[i[1]], vertices.Ptr()[i[2]] );
			}
		}
	}
}

void crHeightmap::Render( void ) {

	if (!heightLoaded) return;

	if (useShader)
		Shader.Activate();

	glBindBuffer(GL_ARRAY_BUFFER, IdVBO[0]);

	if (hasTexture) {
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(crVertex), VBOBUFFER_OFFSET(36) );

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texId[0]);
		Shader.Uniform1i("tex0", 0);
	}

	if (hasNormalmap) {
		glClientActiveTexture(GL_TEXTURE1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(crVertex), VBOBUFFER_OFFSET(44) );

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texId[1]);
		if (useShader) Shader.Uniform1i("normalmap", 1);
	}

	if (hasDetailTex) {
		glClientActiveTexture(GL_TEXTURE2);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(crVertex), VBOBUFFER_OFFSET(52));

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texId[2]);
		if (useShader) Shader.Uniform1i("detailtex", 2);
	}


	if (useShader) {
		Shader.UniformVector3("lightPos", 1, lightPos.ToFloatPtr());
		Shader.UniformVector3("viewPos", 1,  viewPos.ToFloatPtr());
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if (useShader) 
		glEnableVertexAttribArrayARB( Shader.AttributeLoc("tangent") );

	glVertexPointer(3, GL_FLOAT, sizeof(crVertex), NULL);
	glNormalPointer(GL_FLOAT, sizeof(crVertex), VBOBUFFER_OFFSET(sizeof(crVec3)));
	if (useShader)
	  glVertexAttribPointerARB(Shader.AttributeLoc("tangent"), 3, GL_FLOAT, true, sizeof(crVertex), VBOBUFFER_OFFSET(sizeof(crVec3)*2));

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IdVBO[1]);
	for(int i=0; i<height; i++) 
		glDrawElements( GL_TRIANGLE_STRIP, width*2, GL_UNSIGNED_SHORT, VBOBUFFER_OFFSET(2*i*width*sizeof(unsigned short)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	if (useShader)
		glDisableVertexAttribArrayARB( Shader.AttributeLoc("tangent") );
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	if (hasTexture) {
		glClientActiveTexture(GL_TEXTURE0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (hasNormalmap) {
		glClientActiveTexture(GL_TEXTURE1);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (hasDetailTex) {
		glClientActiveTexture(GL_TEXTURE2);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (useShader)
		Shader.Deactivate();
	
	glColor3d(1, 1, 1);
	glPointSize(8.0f);
	glBegin(GL_POINTS);
			glVertex3fv(lightPos.ToFloatPtr());
	glEnd();
	glPointSize(1.0f);

	/* 
	===============================
	Uncomment below to render normals
	===============================
	*/
/*
	glBegin(GL_LINES);
	for (int i=0; i<height*width; i++) {
		glColor3d(1, 0, 0);		
		glVertex3fv(vertices.Ptr()[i].xyz.ToFloatPtr());
		glVertex3fv((vertices.Ptr()[i].xyz + vertices.Ptr()[i].normal).ToFloatPtr());
	
		glColor3d(0, 1, 0);
		glVertex3fv(vertices.Ptr()[i].xyz.ToFloatPtr());
		glVertex3fv((vertices.Ptr()[i].xyz + vertices.Ptr()[i].tangent).ToFloatPtr());
	}
	glEnd();
	glColor3d(1,1,1);
*/
}

float crHeightmap::CollidePoint( crVec3 point ) {
	if( point.x < min.x || point.z < min.z || point.x > max.x || point.z > max.z)
		return point.y;

	crVec3 p = point - min;
	int x = int(p.x);
	int y = int(p.z);

	float heights[4], h;
	heights[0] = heightData.Ptr()[y*width+x];
	heights[1] = heightData.Ptr()[y*width+x+1];
	heights[2] = heightData.Ptr()[(y+1)*width+x];
	heights[3] = heightData.Ptr()[(y+1)*width+x+1];

	float sX = p.x - x;
	float sY = p.z - y;

	if( sX + sY < 1.0f ) {
		h  = heights[0];
		h += (heights[1] - heights[0]) * (sX);
		h += (heights[2] - heights[0]) * (sY);
	} else {
		h  = heights[3];
		h += (heights[1] - heights[3]) * (1.0f - sY);
		h += (heights[2] - heights[3]) * (1.0f - sX);
	}

	return (h+3.0f<point.y)? point.y : h+3.0f;
}

