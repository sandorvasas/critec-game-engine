#include "Water.h"

const char wShader[] = {
 "alfaturo"
};

crWater::crWater( void ) {
	Shader.LoadFromSource((char*)wShader);

	Reflection.Generate(512, 512, 0);
}

crWater::~crWater( void ) {
	DestroyGeometry();
}

void crWater::CreateGeometry( crWaterParams_t wp ) {
	this->params = wp;

	long a = wp.iHeight * wp.iWidth, b;
	verts.Allocate( a );
	indices.Allocate( a * 2 );

	min = crVec3( wp.v3Center.x - (wp.iWidth/2) * wp.fScale,
				  wp.v3Center.y,
				  wp.v3Center.z - (wp.iHeight/2) * wp.fScale );

	int k=0;
	for (int y=0; y<wp.iHeight; y++) {
		for (int x=0; x<wp.iWidth; x++) {
			b = y*wp.iHeight+x;
			verts.Ptr()[b].xyz = crVec3( min.x + x * wp.fScale,
										 wp.v3Center.y,
										 min.z + y * wp.fScale );
			verts.Ptr()[b].st = crVec2( (float)x/wp.iWidth, (float)y/wp.iHeight );
			
			indices.Ptr()[k++] = ((y<wp.iHeight-1)?y+1:y) * wp.iWidth + ((x<wp.iWidth-1)?x+1:x); 
			indices.Ptr()[k++] = (y) * wp.iWidth + ((x<wp.iWidth-1)?x+1:x);
		}
	}

	max = verts.Ptr()[a-1].xyz;

	waterPlane = crVec4( 0, 1, 0, -wp.v3Center.y);

	glGenBuffers(2,&vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crVertex)*verts.Count, verts.Ptr(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	verts.Free();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.Count, indices.Ptr(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	indices.Free();
}

void crWater::DestroyGeometry( void ) {
	glDeleteBuffers(2, &vbo[0]);
}

void crWater::Render( float time ) {
	Shader.Activate();
	glUniform1f(Shader.UniformLoc("time"), time);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer( 2, GL_FLOAT, sizeof(crVertex), BUFFER_OFFSET(3*sizeof(crVec3)));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Reflection.texture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(crVertex), NULL);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	for(long i=0; i<params.iHeight; i++)
		glDrawElements( GL_TRIANGLE_STRIP, params.iWidth*2, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(unsigned int)*i*2*params.iWidth));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableClientState(GL_VERTEX_ARRAY);

	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	Shader.Deactivate();
}

void crWater::BeginRenderReflection( crPlayerCamera* camera,  int w, int h ) {
	scr_w = w;
	scr_h = h;
	crMat4 ReflMat = renderDevice->GetModelViewMatrix();
	savedMat = ReflMat;

	waterPlane = crVec4(0, 1, 0, 0);
	
	glViewport(0, 0, 512, 512);
	Reflection.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera->Look();
	//glTranslatef(0.0f, params.v3Center.y, 0.0f);
	glScaled(1.0, -1.0, 1.0);

	double plane[4] = {0.0, -1.0, 0.0, 0.0};
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, plane);
}

void crWater::EndRenderReflection( void ) {
	glDisable(GL_CLIP_PLANE0);
	Reflection.Unbind();
	glViewport(0, 0, scr_w, scr_h);
	renderDevice->SetTransform(TRANSFORM_LOAD, savedMat.ToFloatPtr());
}
