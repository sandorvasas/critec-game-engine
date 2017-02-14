// Copyright (C) 2007 by sonka

#ifndef __CRITEC_SKYDOME_H__
#define __CRITEC_SKYDOME_H__

#include "../Renderer/GL/GLexp.h"
#include "../Renderer/Texture.h"
#include "../Renderer/ShaderManager.h"
#include "../Math/Math3d.h"
#include "../Framework/Array.h"
#pragma hdrstop


typedef struct crSkyTexParams_s {
//	float			fHour;
	char*			TexFile;
	unsigned int	Id;
} crSkyTexParams_t;

typedef struct crSkyParams_s {
	crVec3				vPosition;
	float				fDampFactor;
	float				fRadius;
	float				fDaytime;
	unsigned int		uiSlices;
	unsigned int		uiSides;
	crSkyTexParams_t	texDay;
	crSkyTexParams_t	texNight;
} crSkyParams_t;


class crSkyDome {
public:
							crSkyDome( void );
	explicit				crSkyDome( crSkyParams_t params );
	virtual					~crSkyDome( void );

	virtual bool			Create( crSkyParams_t params );
	virtual void			Destroy( void );
	virtual void			Render( float time );
	virtual crVec3			GetSunPosition( void );
//	virtual void			ChangeTexture( int index );

protected:
	bool					inited;

	float					currTime;
	crSkyParams_t			params;
	crArray<crVec3>			vertices;
	crArray<crVec2>			texCoords;
	crArray<unsigned short> indices;
	crGLSLShader			Shader;
	unsigned int			idVBO[3];
};

#endif