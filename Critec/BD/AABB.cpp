#include "AABB.h"

void crAABB::BuildCollisionModel (crVec3 *vertices) {
	min = crVec3(+99999, +99999, +99999);
	max = crVec3(-99999, -99999, -99999);
	for (int i=0; i<sizeof(vertices) / sizeof(vertices[0]); i++) {
	    if (vertices[i]>max) max = vertices[i];
		if (vertices[i]<min) min = vertices[i];
	}
}

bool crAABB::isPointInside(crVec3 point) {
	if (point > min && point < max) return true;
	return false;
}

void crAABB::RenderBox() {
	renderDevice->DrawBox( min, max, 0 );
}

crVec3 crAABB::GetCenter() {
	return (min+max)*0.5f;
}