
#ifndef __CRITEC_WATER_H__
#define __CRITEC_WATER_H__

/* !=============================== */
#include "../Renderer/GL/GLexp.h"
#include "../Renderer/ShaderManager.h"
#include "../Renderer/Framebuffer.h"
#include "../Renderer/OpenGLRenderDevice.h"
/* ===============================! */
#include "../Framework/Array.h"
#include "../Math/Math3D.h"
#include "../Camera/PlayerCamera.h"
#include "Vertex.h"
#pragma hdrstop

const float RI_WATER = 1.33333333f;
const float RI_AIR	 = 1.0f;


typedef struct crWaterParams_s {
	int			iWidth;
	int			iHeight;
	crVec3		v3Center;
	float		fScale;
} crWaterParams_t;

class crWater {
public:
							crWater( void );
							~crWater( void );

	void					CreateGeometry( crWaterParams_t params );
	void					DestroyGeometry( void );
//	void					Render( crVec3 sunPos );
	void					BeginRenderReflection( crPlayerCamera* camera, int w, int h );
	void					EndRenderReflection( void );
	void					Render( float time );

protected:
	crGLSLShader			Shader;		
	crFrameBuffer2D			Reflection;
	crMat4					savedMat;
	crArray<crVertex>		verts;
	int						scr_w;
	int						scr_h;
	crVec4					waterPlane;
	crWaterParams_t			params;
	crArray<unsigned int>	indices;
	unsigned int			vbo[2];
	crVec3					min;
	crVec3					max;
};

#endif