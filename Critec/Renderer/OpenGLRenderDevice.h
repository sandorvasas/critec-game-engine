// Copyright (C) 2007 by Sandor Vasas
// 

/*

===================================================================================================

		NOT IMPLEMENTED:
				TRANSFORM_ROTATE
				TRANSFORM_SCALE
				TRANSFORM_TRANSLATE

===================================================================================================

*/

#ifndef __CRITEC_OPENGLRENDERDEVICE_H__
#define __CRITEC_OPENGLRENDERDEVICE_H__

#include "../Math/Math3D.h"
#pragma hdrstop

#include "GL/GLexp.h"

typedef struct crInitOptions_s {
	HWND		hWindow;
	HDC*		hDeviceContext;
	int			iDepthBits;
	int			iColorBits;
	int			iAlphaBits;
	int			iStencilBits;
	bool		bVSync;
	int			iMultiSampling;
} crInitOptions_t;

typedef enum crTransformId_s {
	TRANSFORM_MULT = 0,
	TRANSFORM_LOAD,
	TRANSFORM_ROTATE,
	TRANSFORM_SCALE,
	TRANSFORM_TRANSLATE
} crTransformId_e;

typedef struct crProjAttribs_s {
	double	FieldOfView;
	double	AspectRatio;
	double	nearPlane;
	double	farPlane;
} crProjAttribs_t;


class crOpenGLRenderDevice {
	HGLRC				hRenderContext;
	bool				Initialized;

public:
	crInitOptions_t		InitOptions;
	crProjAttribs_t		ProjAttribs;

public:	
						crOpenGLRenderDevice( void );
						~crOpenGLRenderDevice( void );

	int					Initialize( crInitOptions_t iOpts);
	void				HandleError( int ErrorCode );
	void				Shutdown( void );
	void				SwapBuffers( void );

	void				SetPerspective( crProjAttribs_t projAttr );
	void				SetOrtho( bool ortho = true );
	void				SetTransform( int transformId, float* matrix );
	void				LoadIdentity( void );

	void				DrawSquare( crVec3 p1, crVec3 p2, int texUnit );
	void				DrawBox( crVec3 p1, crVec3 p2, int texUnit );
	void				DrawSprite( crVec2 p1, crVec2 p2, unsigned int texture );
	void				DrawPoint( crVec3 pos, float r, float g, float b );

	crMat4				GetModelViewMatrix( void );
	crMat4				GetProjectionMatrix( void );
	crMat4				GetTextureMatrix( void );
};

extern crOpenGLRenderDevice * renderDevice;

inline
crOpenGLRenderDevice::crOpenGLRenderDevice( void ) {
	hRenderContext = 0;
	Initialized = false;
}

inline
crOpenGLRenderDevice::~crOpenGLRenderDevice( void ) {
	if(Initialized) 
		Shutdown();
}

#endif /* !__CRITEC_OPENGLRENDERDEVICE_H__ */	