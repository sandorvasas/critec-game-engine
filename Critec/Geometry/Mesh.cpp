#include "Mesh.h"

crMesh::crMesh( void ) {
	params = DEFAULT_MESH_PARAMS;
	texCount = 0;
	inited = false;
}

crMesh::crMesh( crMeshParams_t params ) {
	this->params=params;
	texCount = 0;
	inited = false;
}

crMesh::~crMesh( void ) {
	DestroyGeometry();
}

bool crMesh::Def_CreateGeometry( crMeshParams_t wparams ) {
	this->params = wparams;
	inited = false;

	float OneX = params.fXsize / (float)params.uiXunits;
	float OneZ = params.fZsize / (float)params.uiZunits;
	float startX = params.v3Center.x - params.fXsize / 2.f;
	float startZ = params.v3Center.z - params.fZsize / 2.f;
	crVec2 *tOne = new crVec2[texCount];

	/* Generate texture coordinates */
	for(int i=0; i<texCount; i++) {
		tOne[i] = crVec2(	textures[i].s / params.uiXunits, 
							textures[i].t / params.uiZunits  );
		textures[i].texCoords.Allocate( params.uiXunits * params.uiZunits );

		for (unsigned int x=0; x<params.uiXunits; x++) {
			for(unsigned int y=0; y<params.uiZunits; y++) {
				textures[i].texCoords.Ptr()[x*params.uiZunits + y] = crVec2( x * tOne[i].x, y * tOne[i].y );
			}
		}
	}
	
	/* Generate vertex and index data */
	vertices.Allocate( params.uiXunits * params.uiZunits );
	indices.Allocate( params.uiXunits * params.uiZunits * 2 );

	int k = 0;
	for (unsigned int X = 0; X<params.uiXunits; X++) {
		for (unsigned int Z = 0; Z<params.uiZunits; Z++) {
			vertices.Ptr()[X*params.uiZunits + Z] = crVec3(	float(startX + X*OneX), 
															params.v3Center.y, 
															float(startZ + Z*OneZ)	);

			indices.Ptr()[k++] = ((X==params.uiXunits-1)? X : X+1) * params.uiZunits + ((Z==params.uiZunits-1)? Z : Z+1);
			indices.Ptr()[k++] = X * params.uiZunits + ((Z==params.uiZunits-1)? Z : Z+1);

			
		}
	}

	delete [] tOne;
	inited = true;
	return true;
}

void crMesh::Def_DestroyGeometry( void ) {
	vertices.Free();
	normals.Free();
	indices.Free();
	for(int i=0; i<texCount; i++)
		textures[i].texCoords.Free();
}

bool crMesh::Def_AddTexture( const char* FileName, float s, float t ) {
	if (texCount>=MESH_MAX_TEXTURES) return false;

	textures[texCount].s = s;
	textures[texCount].t = t;
	textures[texCount].FileName = FileName;
	textures[texCount].Id = LoadDDSTexture((char*)FileName);
	texCount++;
	
	return true;
}

void crMesh::Def_Render( void ) {
	if(!inited) return;
	for(int i=0; i<texCount; i++) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 8, textures[i].texCoords.Ptr());
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].Id);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 12, vertices.Ptr());
	//glNormalPointer(GL_FLOAT, 12, normals);

	for (unsigned int i=0; i<params.uiXunits; i++)
	//	glDrawArrays(GL_LINE_STRIP, i*params.uiZunits, params.uiZunits);
	glDrawElements(GL_TRIANGLE_STRIP, params.uiZunits*2, GL_UNSIGNED_SHORT, &indices.Ptr()[i*params.uiZunits*2]);

	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	for(int i=0; i<texCount; i++) {
		glClientActiveTexture(GL_TEXTURE0 + i);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

bool crMesh::CreateGeometry( crMeshParams_t wparams ) {
	return Def_CreateGeometry( wparams );
}

void crMesh::DestroyGeometry( void ) {
	Def_DestroyGeometry();
}

bool crMesh::AddTexture( const char* FileName, float s, float t ) {
	return Def_AddTexture( FileName, s, t );
}

void crMesh::Render( void ) {
	Def_Render();
}
