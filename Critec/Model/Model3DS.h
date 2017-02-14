// Copyright (C) 2007 by Sandor Vasas
//
//  Classes whose have secondary constructor:
//				Object3ds
//				Material3ds

/*
========================================================================================
	Known issues:
			Normals calculated wrong
			Animation disabled, not working
========================================================================================
*/

#ifndef __CRITEC_MODEL3DS_H_
#define __CRITEC_MODEL3DS_H_

#include "../renderer/texture.h"
#include "../renderer/shaderManager.h"
#include "../renderer/gl/glexp.h"
#include "../managers/filemanager.h"
#include "../managers/logger.h"
#include "../Framework/System.h"
#pragma hdrstop

class cr3DSModel;


// Definition for debugging 
//#define D


// Logger for debugging 
extern crLogger	Logger;

//=======================
// Texture3ds
//=======================
class Texture3ds {
public:
	unsigned int	Id;
	bool			Exist;
	char*			FileName;
	float			RotationAngle;
	/*

	  ( Have to implement some other attributes )

	*/
public:
		Texture3ds( void );
	void	Initialize ( void );
};

//=======================
// Material3ds
//=======================
class Material3ds {
public:
	char*			Name;
	crVec3			Ambient;
	crVec3			Diffuse;
	crVec3			Specular;
	float			Shininess;
	float			Transparency;

	Texture3ds		mTexture1;
	Texture3ds		mTexture2;
	Texture3ds		mNormal;
	Texture3ds		mOpacity;
	Texture3ds		mSpecular;
	Texture3ds		mShininess;
	Texture3ds		mSelfIllum;
	Texture3ds		mReflection;

public:
	Material3ds( void );
	void		Initialize( void );			
};

//=======================
// Joint3ds
//=======================
/*
typedef struct tagJoint3ds {
	int				Id;
	unsigned int	nRotation;
	unsigned int	nPosition;
	unsigned int	nScale;
	crVec3			kRotation;
	crVec3			kPosition;
	crVec3			kScale;
	
	tagJoint3ds*	Parent;

	void			ApplyTransformations( tagJoint3ds* Joint, unsigned int cFrame );
	void			Recursive_Apply( tagJoint3ds* Joint, unsigned int cFrame );

} Joint3ds, *PJoint3ds;
*/
//=======================
// Triangle3ds
//=======================
typedef struct tagTriangle3ds  {
	unsigned short a, b, c, flag;
} Triangle3ds, *pTriangle3ds;


//=======================
// Mesh3ds
//=======================
class Mesh3ds {
public:
	crVec3				Pivot;
	crVec3*				Vertices;
	crVec3*				Normals;
	crVec3*				tangents;
	crVec2*				TexCoords;
	pTriangle3ds		Triangles;
	unsigned short*		Indices;

	unsigned short		VertexCount;
	unsigned short		TriangleCount;
	unsigned short		TexCoordCount;
	unsigned long		IndexCount;

	Material3ds			Material;
	bool				HasMaterial;

	unsigned short		NodeId;
	Mesh3ds*			ParentNode;
	
	short				PositionCount;
	short				RotationCount;
	short				ScaleCount;
	short				RotationDegreeCount;

	crVec3*				Positions;
	crVec3*				Rotations;
	crVec3*				Scales;
	float*				RotationDegrees;
public:
						Mesh3ds( void );
						~Mesh3ds( void );

	void				ConvertToArray( void );
	void				CreateNormals( void );
	void				Render( crGLSLShader* Shader, crVec3 lightPos, crVec3 viewPos );
	void				RenderNormals( void );
};



//=======================
// Object3ds
//=======================
class Object3ds {
public:
	char*			Name;
	Mesh3ds*		Mesh;

public:
	Object3ds( void );
	~Object3ds( void );
	void	Initialize ( void );
};


//=======================
// cr3DSModelLoader
//=======================
class cr3DSModelLoader {
public:
	crRestoreFile	File;
	Object3ds*		Objects;
	Material3ds*	Materials;
	unsigned int	ObjectCount;
	unsigned int	MaterialCount;
	bool			Loaded;
	bool			Animated;
	char*			TextureDir;

protected:
	unsigned int	startFrame;
	unsigned int	currentFrame;
	unsigned int	endFrame;

	unsigned short*	Nodes;
	int				NodeCount;
	unsigned short* ParentIndices;
	int				ParentIndexCount;

private:
	unsigned short  cParentIndex;
	Object3ds*		CurrentObject;

public:
					cr3DSModelLoader( void );
					~cr3DSModelLoader( void );

	bool			LoadFromFile( char* FileName, char* TextureDir );

protected:
	void			ReadMainChunk( void );

	/* EDIT CHUNK */
	void			ReadEditChunk( void );
	void			ReadObjectChunk( void );
	void			ReadMeshChunk( void );
	void			ReadVerticesChunk( void );
	void			ReadMappingCoordsChunk( void );
	void			ReadTextureChunk( Texture3ds* Texture );
	void			ReadTrianglesChunk( void );
	void			ReadTrianglesMatChunk( void );

	/* MATERIAL CHUNK */
	void			ReadMaterialChunk( void );
	void			ReadColorChunk( crVec3* Color );
	void			ReadTrueColorChunk( crVec3* Color );
	void			ReadRGBColorChunk( crVec3* Color );
	void			ReadPercentChunk( float* Percent );
	void			ReadFloatPercentChunk( float* Percent );
	void			ReadIntPercentChunk( float* Percent );

	/*	KEYFRAMER CHUNK */
	void			ReadKeyframerChunk( void );
	void			ReadFramesChunk( void );
	void			ReadMeshInfoChunk( void );
	void			ReadObjectHierarchyChunk( void );
	void			ReadKeyframePositionsChunk( void );
	void			ReadKeyframeRotationsChunk( void );
	void			ReadKeyframeScalesChunk( void );
	void			ReadPivotChunk( void );
	void			ApplyTrackHierarchy( void );


	unsigned int	ReadName( char** );
	unsigned int	ReadChunkLength( void );
	short			ReadChunkId( void );
	Material3ds*	SearchForMaterial( char* MaterialName );

	void			ConvertToArrays	( void );	

	virtual void	Render( void ) = 0;
	virtual void	Animate( Mesh3ds* pMesh, unsigned int currentFrame ) = 0;
};


//=======================
// cr3DSModel
//=======================
class cr3DSModel : public cr3DSModelLoader {
public:
	crVec3		 Position;
	crGLSLShader Shader;
	bool		 b_Shader;
	crVec3		 lightPos;
	crVec3		 viewPos;

public:
	void		 ModifyParams( crVec3 lightPos, crVec3 viewPos );
	void		 Render( void );
	void		 Animate( Mesh3ds* pMesh, unsigned int currentFrame );
	void		 SetShader( char *file );

protected:
	void	 	 RecAnimate( Mesh3ds* pMesh, unsigned int currentFrame );
	void		 Delay( unsigned int* smtg, unsigned int smtg2 );
};



#endif /* __cr3DSModel_H_ */