#include "Math3D.h"

void ProjectVector(crVec4 plane, crVec3 &vector) {
	crMat3 projMatrix = crMat3( plane.x * plane.x - 1,		plane.y * plane.x ,		plane.z * plane.x,		
					  	    plane.x * plane.y,			plane.y * plane.y - 1,	plane.z * plane.y,		
						    plane.x * plane.z,			plane.y * plane.z,		plane.z * plane.z - 1 );
	vector = projMatrix * vector;
}


crVec3 CalculateNormal( crVec3 v1, crVec3 v2, crVec3 v3 ) {
	return cross( normalize(v2-v1), normalize(v3 - v1) );
}

crVec3 CalculateTangentVector( crVec3 p1, crVec3 p2, crVec3 p3, crVec2 t1, crVec2 t2, crVec2 t3 ) {
	crVec3 v1, v2; 
	crVec2 c1, c2;

	v1 = p2 - p1;
	v2 = p3 - p1;

	c1 = t2 - t1;
	c2 = t3 - t1;

	crVec3 normal = normalize( cross( v1, v2) );
	crVec3 pv1 = v1 - normal * dot(normal, v1);
	crVec3 pv2 = v2 - normal * dot(normal, v2);

	if (c2.x * c1.y > c1.x * c2.y ) {
		c2.x = -c2.x;
		c1.x = -c1.x;
	}

	return normalize((pv1 * c2.x) - (pv2 * c1.x));
}


float clamp( float scalar, float min, float max ) {
	if (scalar>max) scalar = max;
	if (scalar<min) scalar = min;
	return scalar;
}

int	clamp( int scalar, int min, int max ) {
	if (scalar>max) scalar = max;
	if (scalar<min) scalar = min;
	return scalar;
}

int	signum( float a ) {
	if(a < 0.0f) return 1;
	else		 return 0; 
}