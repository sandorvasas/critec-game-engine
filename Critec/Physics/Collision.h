// Copyright (C) 2007 by Sandor Vasas
//

#ifndef __CRITEC_COLLISION_H__
#define __CRITEC_COLLISION_H__

#include "../Geometry/Heightmap.h"
#include "../Camera/PlayerCamera.h"
#include "../Model/Model3DS.h"
#include "../Math/Math3D.h"
#pragma hdrstop

class cr3DSModel;
class crPlayerCamera;
class crHeightmap;

namespace crCollDetect {

	void		Detect_Heightmap_Camera( crHeightmap* hmap, crPlayerCamera* camera );
	void		Detect_Model3ds_Camera( cr3DSModel * model, crPlayerCamera * camera ) ;
	
	bool		isPointInTriangle( crVec3 v1, crVec3 v2, crVec3 v3, crVec3 point );

};


#endif