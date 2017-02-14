
#ifndef __CRITEC_HEIGHTMAP_H__
#define __CRITEC_HEIGHTMAP_H__

#include "../Framework/Array.h"
#include "../Managers/FileManager.h"
#include "../Renderer/ShaderManager.h"
#include "Vertex.h"

typedef struct crHPTex_s {
	float			s;
	float			t;
	char*			fileName;
} crHPTex_t;

typedef struct crHeightmapParams_s {
	crVec3		vOffset;
	crVec2		vScale;
	char*		fileName;
	crHPTex_t	tBase;
	crHPTex_t	tNormal;
	crHPTex_t	tDetail;
} crHeightmapParams_t;


class crHeightmap {
public:

							crHeightmap( void );
	virtual 				~crHeightmap( void );

	virtual float			CollidePoint( crVec3 point );
	virtual bool			CreateGeometry( crHeightmapParams_t hp );
	virtual void			Render( void );
	virtual void			UseShader( bool use );

protected:
	virtual void			CalculateNormals( void );

protected:
	bool					heightLoaded;
	bool					hasTexture;
	bool					hasNormalmap;
	bool					hasDetailTex;

	crVec3					min, max;

	crArray<float>			heightData;
	crArray<unsigned short> indices;
	crArray<crVertex>		vertices;

	unsigned int			texId[3];

	int						height;
	int						width;

	crHeightmapParams_t		hp;

	unsigned int			IdVBO[2];

	bool					useShader;

public:
	crVec3					lightPos;
	crVec3					viewPos;
	crGLSLShader			Shader;
};


inline
void crHeightmap::UseShader( bool use ) {
	useShader=use;
}

#endif