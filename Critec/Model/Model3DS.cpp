
#include "model3ds.h"

#define CH_MAIN	  	    0x4D4D
#define	CH_EDIT3DS	    0x3D3D
#define	CH_OBJECT		0x4000
#define CH_TRIMESH	    0x4100
#define CH_VERTEX		0x4110
#define CH_TRIANGLES	0x4120
#define CH_TRIANGLES_MAT 0x4130
#define CH_MAPCOORDS	0x4140
#define CH_MAT			0xAFFF
#define CH_MAT_NAME	    0xA000	
#define CH_MAT_AMBIENT  0xA010
#define CH_MAT_DIFFUSE	0xA020
#define CH_MAT_SPECULAR	0xA030
#define CH_MAT_SHINE_PC 0xA040
#define CH_MAT_TRANS_PC 0xA050
#define CH_MAT_ISBUMPED 0xA252
#define CH_MAT_TEX1		0xA200
#define CH_MAT_TEX2		0xA33A 
#define CH_MAT_BUMPMAP	0xA230

#define CH_MAT_MAPFILENAME	0xA300
/*
#define CH_MAT_VSCALE_EX	0xA354
#define CH_MAT_USCALE_EX	0xA356
#define CH_MAT_UOFFS_EX		0xA358
#define CH_MAT_VOFFS_EX		0xA35A
#define CH_MAT_ROTANGLE_EX	0xA35C
*/
#define CH_COL_RGB			0x0010
#define CH_COL_TRUE			0x0011
#define CH_PERCENT_INT		0x0030
#define CH_PERCENT_FLOAT	0x0031

#define CH_KEYFRAMER		0xB000
#define CH_KEYF_MESH_INFO	0xB002
#define CH_KEYF_FRAMES		0xB008
#define CH_KEYF_HEADER		0xB00A
#define CH_KEYF_OBJNAME		0xB010
#define CH_KEYF_INSTNAME	0xB011
#define CH_KEYF_PIVOT		0xB013
#define CH_KEYF_POSITION	0xB020
#define CH_KEYF_ROTATION	0xB021
#define CH_KEYF_SCALE		0xB022
#define CH_KEYF_ID			0xB030


crLogger Logger;

/*
=======================
 Material3ds::Initailize();
=======================
*/
Material3ds::Material3ds( void ) {
	Initialize();
}
/*
=======================
 Material3ds::Initailize();
=======================
*/
void Material3ds::Initialize( void ) {
	mNormal      = Texture3ds();
	mTexture1    = Texture3ds();
	mTexture2    = Texture3ds();
	mOpacity     = Texture3ds();
	mShininess   = Texture3ds();
	mSelfIllum   = Texture3ds();
	mReflection  = Texture3ds();
	Transparency = 0.0f;
}

/*
=======================
 Texture3ds::Texture3ds
=======================
*/
Texture3ds::Texture3ds( void ) {
	Exist = false;
	Id	  = 0;
	RotationAngle = 0.0f;
}

/*
=======================
 Object3ds::Object3ds()
=======================
*/
Object3ds::Object3ds( void ) {
	Initialize();
}

/*
=======================
 Object3ds::~Object3ds()
=======================
*/
Object3ds::~Object3ds( void ) {
	delete Mesh;
}

/*
=======================
 Object3ds::Initialize()
=======================
*/
void Object3ds::Initialize( void ) {
	Mesh = new Mesh3ds;
}

/*
=======================
 Mesh3ds::Mesh3ds()
=======================
*/
Mesh3ds::Mesh3ds( void ) {
	TexCoordCount	= 0;
	IndexCount		= 0;
	VertexCount		= 0;
	TriangleCount	= 0;
	HasMaterial		= false;
	//%
	ParentNode		= NULL;
	NodeId			= 65535;
	ScaleCount		= 0;
	PositionCount	= 0;
	RotationCount	= 0;
}

/*
=======================
 Mesh3ds::~Mesh3ds()
=======================
*/
Mesh3ds::~Mesh3ds( void ) {
	if (VertexCount)	 {
		delete [] Vertices;
		delete [] Normals;
		delete [] tangents;
	}

	if (TexCoordCount)	delete [] TexCoords;
	if (TriangleCount)	delete [] Triangles;
	if (IndexCount)		delete [] Indices;
	if (RotationCount)  delete [] Rotations;
	if (PositionCount)  delete [] Positions;
	if (ScaleCount)		delete [] Scales;
}

/*
=======================
 Mesh3ds::CreateNormals()
=======================
*/
void Mesh3ds::CreateNormals( void ) {
	if (!VertexCount || !TriangleCount) return;
	crVec3 normal,tangent, v1, v2;

	crVec3* iNormals = new crVec3[VertexCount];
	tangents = new crVec3[VertexCount];
	Normals = new crVec3[VertexCount];
	
	
	crVec3 temp;
	for (unsigned long i=0; i<TriangleCount; i++) {
		temp = CalculateNormal(	Vertices[Triangles[i].b],	
								Vertices[Triangles[i].a],
								Vertices[Triangles[i].c] );
		iNormals[Triangles[i].a] = temp;
		iNormals[Triangles[i].b] = temp;
		iNormals[Triangles[i].c] = temp;
	}

	for(unsigned long i=0; i<VertexCount; i++) {
		tangent = normal = crVec3( 0, 0, 0 );

		for(unsigned long f=0; f<TriangleCount; f++) {
			if (Triangles[f].a == i || Triangles[f].b == i || Triangles[f].c == i) {
				normal += iNormals[i];

				if (TexCoordCount) 
				tangent += CalculateTangentVector( 	Vertices[Triangles[f].b],	
													Vertices[Triangles[f].a],
													Vertices[Triangles[f].c],
													TexCoords[Triangles[f].b],	
													TexCoords[Triangles[f].a],
													TexCoords[Triangles[f].c] );
				else
					tangent = crVec3(0, 0, 0);
			}

		}
		Normals[i] = normal;
		Normals[i].Normalize();
		tangents[i] = tangent;
		tangents[i].Normalize();
	}

	delete [] iNormals;

#ifdef D
	Logger.Log("Normals have created successfully\n");
#endif
}

/*
=======================
 Mesh3ds::ConvertToArray()
=======================
*/
void Mesh3ds::ConvertToArray( void ) {
	if (!VertexCount || !TriangleCount) return;

	IndexCount = TriangleCount*3;
	Indices = new unsigned short [IndexCount];

	int j=0;
	for (int i=0; i<TriangleCount; i++) {
			Indices[j++] = Triangles[i].a;
			Indices[j++] = Triangles[i].b;
			Indices[j++] = Triangles[i].c;
	}

	// Rotate the mesh 90 degrees around the X axis
	crVec3 v;
	float angle = -PI/2;
	for(unsigned long i=0; i<VertexCount; i++) {
		Vertices[i].Rotate(PI/2, 0.f, 0.f);
	}

	CreateNormals();

#ifdef D
	Logger.Log("Indices array has filled successfully\n");
#endif

}

void Mesh3ds::RenderNormals ( void ) {
	if(!VertexCount) return;
	
	glBegin(GL_LINES);
	for(int i=0; i<VertexCount; i++) {
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(Vertices[i].ToFloatPtr());
		glVertex3fv((Vertices[i] + Normals[i]).ToFloatPtr());
		
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(Vertices[i].ToFloatPtr());
		glVertex3fv((Vertices[i] + tangents[i]).ToFloatPtr());
	}
	glEnd();
	glColor3f(1.f, 1.f, 1.f);
}
/*
=======================
 Mesh3ds::Render()
=======================
*/
void Mesh3ds::Render( crGLSLShader* Shader, crVec3 lightPos, crVec3 viewPos ) {
	if (!VertexCount) return;
	
	if(Shader) Shader->Activate();

	if (Material.mTexture1.Exist && TexCoordCount > 0) {
		glClientActiveTexture( GL_TEXTURE0 );
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 8, TexCoords);
		

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture(GL_TEXTURE_2D, Material.mTexture1.Id);
		if (Shader) Shader->Uniform1i("Texture1", 0);
	} else
		glColor3fv(Material.Diffuse.ToFloatPtr());

	if (Material.mTexture2.Exist && TexCoordCount > 0) {
		glClientActiveTexture( GL_TEXTURE1 );
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 8, TexCoords);

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture(GL_TEXTURE_2D, Material.mTexture2.Id);
		if (Shader) Shader->Uniform1i("Texture2", 1);
	}
	
	if (Material.mNormal.Exist && TexCoordCount > 0) {
		glClientActiveTexture( GL_TEXTURE2 );
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 8, TexCoords);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Material.mNormal.Id);
		if (Shader) Shader->Uniform1i("Normalmap", 2);
	}
	
	if(Shader) Shader->UniformVector3("lightPos", 1, lightPos.ToFloatPtr());
	if(Shader) Shader->UniformVector3("viewPos", 1, viewPos.ToFloatPtr());
	
	unsigned int vA_tan = Shader->AttributeLoc("tangent");
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableVertexAttribArrayARB( vA_tan );

	glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, Vertices);
	glNormalPointer(GL_FLOAT, sizeof(float) * 3, Normals);
	glVertexAttribPointerARB(vA_tan, 3, GL_FLOAT, true, sizeof(float)*3, tangents);

	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, Indices);
	
	glDisableVertexAttribArrayARB( vA_tan );
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


	if (Material.mTexture1.Exist && TexCoordCount > 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glClientActiveTexture(GL_TEXTURE0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (Material.mTexture2.Exist && TexCoordCount > 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);

		glClientActiveTexture(GL_TEXTURE1);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (Material.mNormal.Exist && TexCoordCount > 0) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);

		glClientActiveTexture(GL_TEXTURE2);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	if (Shader) Shader->Deactivate();

	//RenderNormals();

	glColor3f( 1.f, 1.f, 1.f );
}

/*
=======================
 cr3DSModelLoader::cr3DSModelLoader()
=======================
*/
cr3DSModelLoader::cr3DSModelLoader( void ) {
	NodeCount			= 0;
	ObjectCount			= 0;
	MaterialCount		= 0;
	ParentIndexCount	= 0;
	Objects				= NULL;
	Materials			= NULL;
	ParentIndices		= NULL;
	Nodes				= NULL;
	CurrentObject		= NULL;
	Animated			= false;
	Loaded				= false;
}
/*
=======================
 cr3DSModelLoader::~cr3DSModelLoader()
=======================
*/
cr3DSModelLoader::~cr3DSModelLoader( void ) {
	if(ObjectCount)		 free( Objects );
	if(MaterialCount)	 free( Materials );
	if(NodeCount)		 free( Nodes );
	if(ParentIndexCount) free( ParentIndices );
}

/*
=======================
 cr3DSModelLoader::ReadMainChunk()
=======================
*/
unsigned int cr3DSModelLoader::ReadName( char** __str ) {
	int i=0;
	char* str = new char[20];
	do{
		File.ReadChar(&str[i]);
		if(str[i]=='\0')
			break;
		i++;
	}while (i<20);

	*__str = str;
	return true;
}

/*
=======================
 cr3DSModelLoader::ReadChunkLength()
=======================
*/
unsigned int cr3DSModelLoader::ReadChunkLength( void ) {
	unsigned int l;
	File.Seek(-4, SEEK_CUR);
	File.ReadUnsignedInt(&l);
	return l;
}

/*
=======================
 cr3DSModelLoader::ReadChunkId()
=======================
*/
short cr3DSModelLoader::ReadChunkId( void ) {
	short s;
	File.ReadShort(&s);
	return s;
}

/*
=======================
 cr3DSModelLoader::LoadFromFile(..)
=======================
*/
bool cr3DSModelLoader::LoadFromFile( char* FileName, char* TextureDir ) {
	this->TextureDir = TextureDir;

	unsigned char Version;

	if(!File.Open(FileName)) return false;

#ifdef D
	Logger.Open("3ds_log.txt");
	Logger.Log("Loading %s\n", FileName);
#endif

	File.Seek(28L, SEEK_SET);
	File.ReadByte(&Version);
	
	/*
		 RESTORE TO "Version < 3"
	 */
	if (Version < 0) {
#ifdef D
	Logger.Log("Invalid file version ( Version<3 )\n");
#endif
		MSGBOX("Invalid file version (%d)", Version);
		return false;
	}
#ifdef D
	Logger.Log("3ds Version: %d\n", Version);
#endif	
	
	File.Seek(2, SEEK_SET);

	ReadMainChunk();

#ifdef D
	Logger.Log("================================\nMaterialCount: %d\n", MaterialCount);
	for (unsigned int i=0; i<MaterialCount; i++)
		Logger.Log("Material%d's name: %s    Has texture: %s\n", i, Materials[i].Name, bool_str(Materials[i].mTexture1.Exist));
	Logger.Log("================================\n");

	Logger.Log("================================\nObjectCount: %d\n", ObjectCount);
	for (unsigned int i=0; i<ObjectCount; i++)
	 if (Objects[i].Mesh->HasMaterial)
		Logger.Log("Object%d s materialname: %s\n", i, Objects[i].Mesh->Material.Name);
	Logger.Log("================================\n");
#endif

	File.Close();

	ConvertToArrays();
	
	Loaded = true;
	return true;
}

/*
=======================
 cr3DSModelLoader::ReadMainChunk()
=======================
*/
void cr3DSModelLoader::ReadMainChunk( void ) {
	unsigned int	ChunkLength;
	unsigned int	ChunkPos;
	unsigned short	ChunkId;
	unsigned long long filesize = File.GetSize();

	File.ReadUnsignedInt(&ChunkLength);
		
	while (File.Tell() < filesize ) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {

			case CH_EDIT3DS:		
				ReadEditChunk();
			break;

		//	case CH_KEYFRAMER:
		//		ReadKeyframerChunk();
		//	break;

			default:		
				File.Seek(ChunkLength + ChunkPos, SEEK_SET);
		}
	}
#ifdef D
	Logger.Log("Exited from MAIN chunk\n");
#endif
}

/*
=======================
 cr3DSModelLoader::ReadEditChunk()
=======================
*/
void cr3DSModelLoader::ReadEditChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	  = File.Tell() - 6;
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;

#ifdef D
	Logger.Log("Edit3ds chunk found. Length: %d\n", tChunkLength);
#endif

	while (unsigned int (File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch (ChunkId) {
			
			case CH_OBJECT:
					ReadObjectChunk();
			break;

			case CH_MAT:
					ReadMaterialChunk();
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

#ifdef D
	Logger.Log("Exited from EDIT3DS chunk\n");
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadObjectChunk()
=======================
*/
void cr3DSModelLoader::ReadObjectChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	 = File.Tell() - 6;
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;

	Objects = (Object3ds*) realloc(Objects, sizeof(Object3ds) * ++ObjectCount);
	Objects[ObjectCount-1].Initialize();

	ReadName(&Objects[ObjectCount-1].Name);

#ifdef D
	Logger.Log("Object chunk found. Length: %d; Name: %s\n", tChunkLength, Objects[ObjectCount-1].Name);
#endif

	while (unsigned int (File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch (ChunkId) {
			case CH_TRIMESH:
				ReadMeshChunk();
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}

	}

#ifdef D
	Logger.Log("Exited from OBJECT chunk\n");
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadMaterialChunk()
=======================
*/
void cr3DSModelLoader::ReadMaterialChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;
	unsigned int ChunkLength, ChunkPos;
	unsigned short ChunkId;

#ifdef D
Logger.Log(">>Material chunk found\n");
#endif

	while (unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_MAT_NAME:
					Materials = (Material3ds*) realloc( Materials, sizeof(Material3ds) * ++MaterialCount );
					Materials[MaterialCount-1].Initialize();

					ReadName(&Materials[MaterialCount-1].Name);
#ifdef D
Logger.Log(">>Material Name: '%s'\n", Materials[MaterialCount-1].Name);
#endif
			break;


			case CH_MAT_DIFFUSE:
#ifdef D
	Logger.Log(">>Diffuse\n");
#endif
				ReadColorChunk(&Materials[MaterialCount-1].Diffuse);
			break;

			case CH_MAT_AMBIENT:
#ifdef D
	Logger.Log(">>Ambient\n");
#endif
				ReadColorChunk(&Materials[MaterialCount-1].Ambient);
			break;

			case CH_MAT_SPECULAR:
#ifdef D
	Logger.Log(">>Specular\n");
#endif
				ReadColorChunk(&Materials[MaterialCount-1].Specular);
			break;

			case CH_MAT_SHINE_PC:
#ifdef D
	Logger.Log(">>Shininess\n");
#endif
				ReadPercentChunk(&Materials[MaterialCount-1].Shininess);
			break;

			case CH_MAT_TRANS_PC:
#ifdef D
	Logger.Log(">>Transparency\n");
#endif
				ReadPercentChunk(&Materials[MaterialCount-1].Transparency);
			break;

			case CH_MAT_TEX1:
				ReadTextureChunk(&Materials[MaterialCount-1].mTexture1);
#ifdef D
				Logger.Log("!!  >>Texture1.Id = %d\n", Materials[MaterialCount-1].mTexture1.Id);
#endif
			break;

			case CH_MAT_TEX2:
				ReadTextureChunk(&Materials[MaterialCount-1].mTexture2);
#ifdef D
				Logger.Log("!!  >>mTexture2.Id = %d\n", Materials[MaterialCount-1].mTexture2.Id);
#endif
			break;

			case CH_MAT_BUMPMAP:
				ReadTextureChunk(&Materials[MaterialCount-1].mNormal);
#ifdef D
				Logger.Log("!!  >>mNormal.Id = %d\n", Materials[MaterialCount-1].mNormal.Id);
#endif
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}
}

/*
=======================
 cr3DSModelLoader::ReadMeshChunk()
=======================
*/
void cr3DSModelLoader::ReadMeshChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	  = File.Tell() - 6;
	unsigned int ChunkLength, ChunkPos;
	unsigned short ChunkId;
	

#ifdef D
	Logger.Log("Mesh chunk found. Length: %d\n", tChunkLength);
#endif


	while (unsigned int (File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch (ChunkId) {
			case CH_VERTEX:
					ReadVerticesChunk();
			break;

			case CH_MAPCOORDS:
					ReadMappingCoordsChunk();
			break;

			case CH_TRIANGLES:
					ReadTrianglesChunk();
			break;

			default:
				File.Seek(ChunkPos  +  ChunkLength, SEEK_SET);
		}
	}

#ifdef D
	Logger.Log("Exited from MESH chunk\n");
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadVerticesChunk()
=======================
*/
void cr3DSModelLoader::ReadVerticesChunk( void ) {
	unsigned int ChunkLength = ReadChunkLength();
	unsigned int ChunkPos	 = File.Tell() - 6;

	File.ReadUnsignedShort(&Objects[ObjectCount-1].Mesh->VertexCount);
#ifdef D
	Logger.Log("  Vertices chunk found. Length: %d; VertexCount: %d\n", ChunkLength, Objects[ObjectCount-1].Mesh->VertexCount);
#endif

	Objects[ObjectCount-1].Mesh->Vertices = new crVec3[Objects[ObjectCount-1].Mesh->VertexCount];

	for (int i=0; i<Objects[ObjectCount-1].Mesh->VertexCount; i++) {
		File.ReadcrVec3(&Objects[ObjectCount-1].Mesh->Vertices[i]);
	}
#ifdef D
	Logger.Log("  Vertices read\n");
#endif

	File.Seek(ChunkPos + ChunkLength, SEEK_SET);
}

/*
=======================
  cr3DSModelLoader::ReadMappingCoordsChunk();
=======================
*/
void cr3DSModelLoader::ReadMappingCoordsChunk( void ) {
	unsigned int ChunkLength = ReadChunkLength();
	unsigned int ChunkPos	 = File.Tell()-6;

	File.ReadUnsignedShort(&Objects[ObjectCount-1].Mesh->TexCoordCount);

#ifdef D
	Logger.Log("Texture coordinates chunk found. Length: %d; Count: %d\n", ChunkLength, Objects[ObjectCount-1].Mesh->TexCoordCount);
#endif

	Objects[ObjectCount-1].Mesh->TexCoords = new crVec2[Objects[ObjectCount-1].Mesh->TexCoordCount];

	for(int i=0; i<Objects[ObjectCount-1].Mesh->TexCoordCount; i++) {
		File.ReadcrVec2(&Objects[ObjectCount-1].Mesh->TexCoords[i]);
	}
#ifdef D
	Logger.Log("TexCoords read\n");
#endif

	File.Seek(ChunkPos + ChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadTrianglesChunk()
=======================
*/
void cr3DSModelLoader::ReadTrianglesChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	 = File.Tell() - 6;

	File.ReadUnsignedShort(&Objects[ObjectCount-1].Mesh->TriangleCount);

#ifdef D
	Logger.Log("Triangles chunk found. Length: %d; Count: %d\n", tChunkLength, Objects[ObjectCount-1].Mesh->TriangleCount);
#endif
	
	Objects[ObjectCount-1].Mesh->Triangles = new Triangle3ds[Objects[ObjectCount-1].Mesh->TriangleCount];

	for (int i=0; i<Objects[ObjectCount-1].Mesh->TriangleCount; i++) {
		File.Read(&Objects[ObjectCount-1].Mesh->Triangles[i], sizeof(unsigned short)*4);
	}

#ifdef D
	Logger.Log("Triangles read\n");
#endif

	unsigned int ChunkLength, ChunkPos;
	unsigned short ChunkId;

	Objects[ObjectCount-1].Mesh->HasMaterial = false;

	while( unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {

			case CH_TRIANGLES_MAT:
					ReadTrianglesMatChunk();
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadTrianglesMatChunk()
=======================
*/
void cr3DSModelLoader::ReadTrianglesMatChunk( void ) {
	unsigned int tChunkPos = File.Tell() - 6;
	unsigned int tChunkLength = ReadChunkLength();
	char*	MaterialName;

	Objects[ObjectCount-1].Mesh->HasMaterial = true;

	ReadName(&MaterialName);

#ifdef D
	Logger.Log(" *** Triangles material chunk found ***\n  Name = '%s'\n", MaterialName);
#endif

	Objects[ObjectCount-1].Mesh->Material =	*SearchForMaterial(MaterialName);
	//Objects[ObjectCount-1].Mesh->Material = Materials[MaterialCount-1];
#ifdef D
	Logger.Log("  -> Objects[ObjectCount-1].Mesh.Material: \n"
			   "     mTexture1 = %s\n"
			   "     mTexture2 = %s\n"
			   "     mNormal   = %s\n"
			   "     Transparency = %2.5f\n\n",
			   bool_str(Objects[ObjectCount-1].Mesh->Material.mTexture1.Exist),
			   bool_str(Objects[ObjectCount-1].Mesh->Material.mTexture2.Exist),
			   bool_str(Objects[ObjectCount-1].Mesh->Material.mNormal.Exist),
			   Objects[ObjectCount-1].Mesh->Material.Transparency);
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadTextureChunk
=======================
*/
void cr3DSModelLoader::ReadTextureChunk( Texture3ds* Texture ) {
	unsigned int tChunkPos = File.Tell() - 6,
				 tChunkLength = ReadChunkLength();
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;
	
	Texture->Exist = true;

	while (unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_MAT_MAPFILENAME: {
				ReadName(&Texture->FileName);

#ifdef D
Logger.Log(" >> Texture Name: %s\n", Texture->FileName);
#endif
				
				/*
					Modifiy the texture file extension to .dds
				*/
				char strTex[2048];
				strcpy_s(strTex, 2048, TextureDir);

				int lt = strlen(Texture->FileName);
				Texture->FileName[lt-3] = 'd';
				Texture->FileName[lt-2] = 'd';
				Texture->FileName[lt-1] = 's';
				strcat_s(strTex, 2048, Texture->FileName);
#ifdef D
Logger.Log("3 %s\n", Texture->FileName);
#endif

				Texture->Id = LoadDDSTexture(strTex);
			}
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadColorChunk
=======================
*/
void cr3DSModelLoader::ReadColorChunk( crVec3* Color  ) {
	unsigned int tChunkPos     = File.Tell() - 6, 
				 tChunkLength  = ReadChunkLength();
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;

	while (unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_COL_RGB:
				ReadRGBColorChunk(Color);
			break;

			case CH_COL_TRUE:
				ReadTrueColorChunk(Color);
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadTrueColorChunk
=======================
*/
void cr3DSModelLoader::ReadTrueColorChunk( crVec3* Color ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	  = File.Tell() - 6;
	unsigned char rgb_color[3];

	File.ReadByte(&rgb_color[0]);
	File.ReadByte(&rgb_color[1]);
	File.ReadByte(&rgb_color[2]);
	
	*Color = crVec3( rgb_color[0] / 256.f, 
				   rgb_color[1] / 256.f,
				   rgb_color[2] / 256.f );

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);

#ifdef D
	Logger.Log("TrueColor read (%2.2f, %2.2f, %2.2f)\n", Color->x, Color->y, Color->z);
#endif
}

/*
=======================
 cr3DSModelLoader::ReadRGBColorChunk
=======================
*/
void cr3DSModelLoader::ReadRGBColorChunk( crVec3* Color ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos	  = File.Tell() - 6;
	File.ReadcrVec3(Color);
	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadPercentChunk
=======================
*/
void cr3DSModelLoader::ReadPercentChunk( float* Percent ) {
	unsigned int tChunkPos = File.Tell()-6,
				 tChunkLength = ReadChunkLength();
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;

	while (unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_PERCENT_INT:
				ReadIntPercentChunk(Percent);
#ifdef D
				Logger.Log("=== Int Percent Chunk: %3.2f ====================\n", *Percent);
#endif
			break;

			case CH_PERCENT_FLOAT:
				ReadFloatPercentChunk(Percent);
#ifdef D
				Logger.Log("=== Float Percent Chunk: %3.2f ====================\n", *Percent);
#endif
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadFloatPercentChunk
=======================
*/
void cr3DSModelLoader::ReadFloatPercentChunk( float* Percent ) {
	unsigned int tChunkPos = File.Tell() - 6,
				 tChunkLength = ReadChunkLength();

	File.ReadFloat(Percent);

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadIntPercentChunk
=======================
*/
void cr3DSModelLoader::ReadIntPercentChunk( float* Percent ) {
	unsigned int tChunkPos = File.Tell() - 6,
				 tChunkLength = ReadChunkLength();

	signed short iPercent;
	File.ReadShort(&iPercent);

	*Percent = (float) iPercent/100.f;

	File.Seek(tChunkPos + tChunkLength, SEEK_SET); 
}

/*
=======================
 cr3DSModelLoader::ReadKeyframerChunk()
=======================
*/
void cr3DSModelLoader::ReadKeyframerChunk() {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos = File.Tell()-6;
	unsigned int ChunkLength, ChunkPos;
	unsigned short ChunkId;

#ifdef D
 Logger.Log("Keyframer chunk found!\n");
#endif

	while( unsigned int (File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_KEYF_FRAMES:
				ReadFramesChunk();
			break;

			case CH_KEYF_MESH_INFO:	
				ReadMeshInfoChunk();
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	ApplyTrackHierarchy();
	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadFramesChunk()
=======================
*/ 
void cr3DSModelLoader::ReadFramesChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;

	File.ReadUnsignedInt(&startFrame);
	File.ReadUnsignedInt(&endFrame);

#ifdef D
	Logger.Log("FRAMES\n==============\n  startFrame: %d\n  endFrame: %d\n==============\n", startFrame, endFrame);
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadMeshInfoChunk()
=======================
*/
void cr3DSModelLoader::ReadMeshInfoChunk( void ){
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;
	unsigned int ChunkPos, ChunkLength;
	unsigned short ChunkId;

	unsigned short temp_NodeId;

	Animated = true;

	ParentIndices = (unsigned short*) realloc(ParentIndices, sizeof(unsigned short) * ++ParentIndexCount);
	ParentIndices[ParentIndexCount-1] = 65535;

	Nodes = (unsigned short*) realloc(Nodes, sizeof(unsigned short) * ++NodeCount);
	Nodes[NodeCount-1] = 65535;

	while(unsigned int(File.Tell()) < tChunkPos + tChunkLength) {
		ChunkPos = File.Tell();
		File.ReadUnsignedShort(&ChunkId);
		File.ReadUnsignedInt(&ChunkLength);

		switch(ChunkId) {
			case CH_KEYF_HEADER:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
			break;

			case CH_KEYF_ID:
				File.ReadUnsignedShort(&temp_NodeId);
#ifdef D
				Logger.Log(" nodeId: %d\n", temp_NodeId);
#endif
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
			break;

			case CH_KEYF_OBJNAME:
				ReadObjectHierarchyChunk();
			break;

			case CH_KEYF_SCALE:
				ReadKeyframeScalesChunk();
			break;

			case CH_KEYF_ROTATION:
				ReadKeyframeRotationsChunk();
			break;

			case CH_KEYF_POSITION:
				ReadKeyframePositionsChunk();
			break;

			case CH_KEYF_PIVOT:
				ReadPivotChunk();
			break;

			default:
				File.Seek(ChunkPos + ChunkLength, SEEK_SET);
		}
	}

	CurrentObject->Mesh->NodeId     = temp_NodeId;
	ParentIndices[temp_NodeId]      = cParentIndex;

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadObjectHierarchyChunk()
=======================
*/
void cr3DSModelLoader::ReadObjectHierarchyChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;
	char* name;

	ReadName(&name);

#ifdef D
	Logger.Log(" Hierarchy.\n Object's name: %s\n", name);
#endif

	for (unsigned int i=0; i<ObjectCount; i++) {
		if (CompareString(Objects[i].Name, name)) {
			Nodes[NodeCount-1] = i;

			CurrentObject = &Objects[i];
			break;
		}
	}

	File.Seek(4, SEEK_CUR);
	File.ReadUnsignedShort(&cParentIndex);

#ifdef D
	Logger.Log("    CurrentObject.Name = %s\n"
			   "    cParentIndex       = %d\n",
			   CurrentObject->Name, cParentIndex);
#endif

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadKeyframePositionsChunk()
=======================
*/
void cr3DSModelLoader::ReadKeyframePositionsChunk( void ){
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;

#ifdef D
	Logger.Log ("]> Keyframe positions <[\n");
#endif

	File.Seek(5*sizeof(short), SEEK_CUR);
	File.ReadShort(&CurrentObject->Mesh->PositionCount);
	File.Seek(sizeof(short), SEEK_CUR);

	CurrentObject->Mesh->Positions = new crVec3[endFrame+2];

#ifdef D
	Logger.Log ("   PositionCount : %d\n", CurrentObject->Mesh->PositionCount);
#endif

	for (unsigned int i=0; i<= endFrame+1; i++) {
		if (int(i) < CurrentObject->Mesh->PositionCount) {
			File.Seek(sizeof(short) + sizeof(long), SEEK_CUR);
			File.ReadcrVec3(&CurrentObject->Mesh->Positions[i]);
			CurrentObject->Mesh->Positions[i].Rotate(PI/2.f, 0.f, 0.f);
		}
		else
			CurrentObject->Mesh->Positions[i] = CurrentObject->Mesh->Positions[ CurrentObject->Mesh->PositionCount-1 ];
	}

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadKeyframeRotationsChunk()
=======================
*/
void cr3DSModelLoader::ReadKeyframeRotationsChunk( void ){
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;

#ifdef D
	Logger.Log ("]> Keyframe rotations <[\n");
#endif

	File.Seek(5*sizeof(short), SEEK_CUR);
	File.ReadShort(&CurrentObject->Mesh->RotationCount);
	File.Seek(sizeof(short), SEEK_CUR);
	
	crVec3* tempRot				= new crVec3			[CurrentObject->Mesh->RotationCount];
	float* RotationDegrees		= new float			[CurrentObject->Mesh->RotationCount];
	unsigned short* FrameNumbers= new unsigned short[CurrentObject->Mesh->RotationCount];

#ifdef D
	Logger.Log ("   RotationCount: %d\n", CurrentObject->Mesh->RotationCount);
#endif

	for(int i=0; i< CurrentObject->Mesh->RotationCount; i++)  {
		File.ReadUnsignedShort(&FrameNumbers[i]);
		File.Seek(sizeof(long), SEEK_CUR);

		File.ReadFloat(&RotationDegrees[i]);
		
		RotationDegrees[i] *= 180/PI;

		File.ReadcrVec3(&tempRot[i]);
		tempRot[i].Rotate(PI/2.f, 0.f, 0.f);
	}

	CurrentObject->Mesh->Rotations = new crVec3[endFrame + 2];
	CurrentObject->Mesh->Rotations[0] = tempRot[0];

	CurrentObject->Mesh->RotationDegrees = new float[endFrame+2];
	CurrentObject->Mesh->RotationDegrees[0] = RotationDegrees[0];

	int currentkey = 1;

	for(unsigned int i=1; i<endFrame; i++) {
		if (currentkey < CurrentObject->Mesh->RotationCount) {
			float rotDegree = RotationDegrees[currentkey] / (FrameNumbers[currentkey] - FrameNumbers[currentkey-1]);
			
			CurrentObject->Mesh->Rotations[i]       = tempRot[currentkey];
			CurrentObject->Mesh->RotationDegrees[i] = rotDegree;

			if (FrameNumbers[currentkey] <= i) 
				currentkey++;
		}
		else {
			CurrentObject->Mesh->Rotations[i] = tempRot[CurrentObject->Mesh->RotationCount-1];
			CurrentObject->Mesh->RotationDegrees[i] = 0.0f;
		}

	}

	delete [] tempRot;
	delete [] RotationDegrees;
	delete [] FrameNumbers;

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ReadKeyframeScalesChunk()
=======================
*/
void cr3DSModelLoader::ReadKeyframeScalesChunk( void ){
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;

#ifdef D
	Logger.Log ("]> Keyframe scales <[\n");
#endif

	File.Seek(5*sizeof(short), SEEK_CUR);
	File.ReadShort(&CurrentObject->Mesh->ScaleCount);
	File.Seek(sizeof(short), SEEK_CUR);

#ifdef D
	Logger.Log(" Number of scales: %d\n", CurrentObject->Mesh->ScaleCount);
#endif

	CurrentObject->Mesh->Scales = new crVec3[endFrame+2];

	for(unsigned int i=0; i<=endFrame+1; i++) {
		if(int(i) < CurrentObject->Mesh->ScaleCount) {
			File.Seek(sizeof(short) + sizeof(long), SEEK_CUR);
			File.ReadcrVec3(&CurrentObject->Mesh->Scales[i]);
			CurrentObject->Mesh->Scales[i].Rotate(PI/2.f, 0.f, 0.f);
		}
		else
			CurrentObject->Mesh->Scales[i] = CurrentObject->Mesh->Scales[ CurrentObject->Mesh->ScaleCount-1 ];
	}


	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::ApplyTrackHierarchy()
=======================
*/
void cr3DSModelLoader::ApplyTrackHierarchy( void ) {

	//Set each object's parentNode 
	for (int i=0; i< NodeCount; i++) {

		Object3ds* pObject = &Objects[i];

		if (pObject->Mesh->NodeId==65535)
			continue;

		for (int j=i+1; j<NodeCount; j++) {
			Object3ds* cObject = &Objects[Nodes[j]];

			if (pObject->Mesh->NodeId == ParentIndices[j])
				cObject->Mesh->ParentNode = pObject->Mesh;
		}
	}

	// If the object hasn't got a parent, substract the pivot point from its vertices
/*	for(int i=0; i<ObjectCount; i++) {
	//	if (!Objects[i].Mesh->ParentNode)
		{
			for(int j = 0; j< Objects[i].Mesh->VertexCount; j++) 
				Objects[i].Mesh->Vertices[j] -= Objects[i].Mesh->Positions[0] + Objects[i].Mesh->Pivot;
		}
	}*/
}

/*
=======================
 cr3DSModelLoader::ReadPivotChunk()
=======================
*/
void cr3DSModelLoader::ReadPivotChunk( void ) {
	unsigned int tChunkLength = ReadChunkLength();
	unsigned int tChunkPos    = File.Tell() - 6;

	File.ReadcrVec3(&CurrentObject->Mesh->Pivot);

	File.Seek(tChunkPos + tChunkLength, SEEK_SET);
}

/*
=======================
 cr3DSModelLoader::SearchForMaterial
=======================
*/
Material3ds* cr3DSModelLoader::SearchForMaterial( char* MaterialName ) {

#ifdef D
	Logger.Log("## Searching for material: %s\n## MaterialCount: %d\n", MaterialName, MaterialCount);
#endif
  
	for (unsigned int i=0; i<MaterialCount; i++) {
#ifdef D
		Logger.Log(" ## MaterialName      = '%s'\n", MaterialName);
		Logger.Log(" ## Materials[i].Name = '%s'\n", Materials[i].Name);
#endif 
		if (CompareString(Materials[i].Name, MaterialName)) {
#ifdef D
		Logger.Log("## Material (%s) found\n", Materials[i].Name);
#endif
			return ( &Materials[i] );
		}
	}

#ifdef D
		Logger.Log("## Material (%s) could not be found\n", MaterialName);
#endif

	static Material3ds mat;
	mat.Name = "No material";
	return &mat;
}

/*
=======================
 cr3DSModelLoader::ConvertToArrays()
=======================
*/
void cr3DSModelLoader::ConvertToArrays( void ) {
	for (unsigned int i=0; i<ObjectCount; i++) {
		Objects[i].Mesh->ConvertToArray();
	}
}

/*
=======================
  cr3DSModel::Render()
=======================
*/
void cr3DSModel::Render( void ) {
	if (!Loaded) return;

/*	if (Animated) {
		Delay(&currentFrame, 3);
		currentFrame %= endFrame;
		if(!currentFrame) currentFrame++;

		for (unsigned int i=0; i<ObjectCount; i++) {
			glPushMatrix();
				if(Objects[i].Mesh->ParentNode) 
					Animate(Objects[i].Mesh->ParentNode, currentFrame);

				RecAnimate(Objects[i].Mesh, currentFrame);

				Objects[i].Mesh->Render(&Shader, lightPos, viewPos);
			glPopMatrix();
		}
	}
	else*/
		for (unsigned int i=0; i<ObjectCount; i++) {
			Objects[i].Mesh->Render(&Shader, lightPos, viewPos);
		}
}

/*
=======================
  cr3DSModel::Delay()
=======================
*/
void cr3DSModel::Delay( unsigned int* smtg, unsigned int smtg2 ) {
	static unsigned int b = 0;
	b++;
	if (b==smtg2) {
		b = 0;
		*smtg += 1;
	}
}

/*
=======================
  cr3DSModel::Animate()
=======================
*/
void cr3DSModel::Animate( Mesh3ds* pMesh, unsigned int currentFrame ) {
	this->currentFrame = currentFrame;
	
	if(pMesh->ParentNode)
		Animate(pMesh->ParentNode, currentFrame);

	RecAnimate(pMesh, currentFrame);
}

/*
=======================
  cr3DSModel::RecAnimate()
=======================
*/
void cr3DSModel::RecAnimate( Mesh3ds* pMesh, unsigned int currentFrame ) {

		glTranslatef(pMesh->Positions[currentFrame].x, 
					 pMesh->Positions[currentFrame].y, 
					 pMesh->Positions[currentFrame].z );

		for (unsigned int j=1; j<=currentFrame; j++) {
			crVec3  Rotation = pMesh->Rotations[j];
			float cRotationDegree = pMesh->RotationDegrees[j];
			glRotatef(cRotationDegree, Rotation.x, Rotation.y, Rotation.z);
		}
}


/*
=======================
  cr3DSModel::SetShader()
=======================
*/
void cr3DSModel::SetShader( char *file ) {
	Shader.LoadFromFile( file );
	
	b_Shader = true;
}

/*
=======================
  cr3DSModel::ModifyParams()
=======================
*/
void cr3DSModel::ModifyParams( crVec3 lightPos, crVec3 viewPos ) {
	this->viewPos = viewPos;
	this->lightPos = lightPos;
}