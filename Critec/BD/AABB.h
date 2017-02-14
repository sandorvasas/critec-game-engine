// Copyright (C) 2007 by Sandor Vasas
//

#ifndef __CRITEC_AABB_H__
#define __CRITEC_AABB_H__

#include "../renderer/OpenGLRenderDevice.h"
#include "../math/math3d.h"
#pragma hdrstop

struct crAABB {
	
	crVec3		min, max;
	int			PointsVisible;
	
public:
	crVec3		GetCenter( void );
	void		BuildCollisionModel( crVec3* vertices );
	void		RenderBox( void );
	bool		isPointInside( crVec3 point );
};


#endif /* __AABB_H_ */