
#ifndef __CRITEC_MESH_H__
#define __CRITEC_MESH_H__

#include "../Framework/Array.h"
#include "../Math/Math3D.h"
#include "../Renderer/Texture.h"

const int MESH_MAX_TEXTURES = 8;


typedef struct crMeshParams_s {
	crVec3			v3Center;
	float			fXsize;
	float			fZsize;
	unsigned int	uiXunits;
	unsigned int	uiZunits;
} crMeshParams_t;

const crMeshParams_t DEFAULT_MESH_PARAMS = { crVec3(0.f, 0.f, 0.f), 10.f, 10.f, 10, 10 };

typedef struct crMeshTexture_s {
	const char*		FileName;
	float			s;
	float			t;
	unsigned int	Id;
	crArray<crVec2> texCoords;
} crMeshTexture_t;


class crMesh {
public:
							crMesh( void );
	explicit				crMesh( crMeshParams_t params );
	virtual					~crMesh( void );

	virtual bool			CreateGeometry( crMeshParams_t wparams = DEFAULT_MESH_PARAMS );
	virtual void			DestroyGeometry( void );
	virtual bool			AddTexture( const char* FileName, float s, float t );
	virtual void			Render( void );

protected:
	bool					Def_CreateGeometry( crMeshParams_t wparams = DEFAULT_MESH_PARAMS );
	void					Def_DestroyGeometry( void );
	bool					Def_AddTexture( const char* FileName, float s, float t );
	void					Def_Render( void );

public:
	crMeshParams_t			params;

protected:
	crArray<crVec3>			vertices;
	crArray<crVec3>			normals;
	crArray<unsigned short>	indices;
	crMeshTexture_t			textures[MESH_MAX_TEXTURES];
	int						texCount;
	bool					inited;
};

#endif /* !__CRITEC_MESH_H__ */