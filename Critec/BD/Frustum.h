// Copyright (C) 2007 by Sandor Vasas
//
#ifndef __CRITEC_FRUSTUM_H_
#define __CRITEC_FRUSTUM_H_

#include "../renderer/OpenGLRenderDevice.h"
#include "AABB.h"
#include "../math/math3d.h"
#pragma hdrstop

struct AABB;

class crFrustum {
protected:
	enum {
		TOP = 0, BOTTOM, 
		LEFT,	 RIGHT, 
		BACK,    FRONT
	};
	crVec4	frustumPlanes[6];

public:
	
	void	Update( void );
	bool	isPointInside( crVec3 point );
	bool	isSphereInside( crVec3 point, float radius );
	bool	isAABBInside( crAABB& bounds );
};

#endif