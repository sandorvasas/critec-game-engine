// Copyright (C) 2007 by Sandor Vasas
//

#ifndef __CRITEC_MATH3D_H__
#define __CRITEC_MATH3D_H__

#include <windows.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include "Quaternion.h"

#ifndef __PI__
#define __PI__
 const float PI = 3.1415926535f;
#endif
const float TWOPI = 6.283185308f;
const float e  = 2.718281828459045f;
const float GFORCE = 6.6742f;

#define TORAD (PI/180.f)
#define TODEG (180.f/PI)
#define EPSILON 1/32


void				ProjectVector( crVec4 plane, crVec3 &vector );
crVec3				CalculateNormal( crVec3 v1, crVec3 v2, crVec3 v3 );
crVec3				CalculateTangentVector( crVec3 p1, crVec3 p2, crVec3 p3, crVec2 t1, crVec2 t2, crVec2 t3 );

float				clamp( float scalar, float min, float max );
int					clamp( int scalar, int min, int max );
int					signum( float a );

#endif