#include "frustum.h"

void crFrustum::Update() {
	
	crMat4 projMatrix,
		 modelMatrix,
		 frustumMatrix;

	projMatrix = renderDevice->GetProjectionMatrix();
	modelMatrix = renderDevice->GetModelViewMatrix();

	frustumMatrix = (projMatrix * modelMatrix).Transpose();

	frustumPlanes[LEFT].x = frustumMatrix[3]   + frustumMatrix[0];
	frustumPlanes[LEFT].y = frustumMatrix[7]   + frustumMatrix[4];
	frustumPlanes[LEFT].z = frustumMatrix[11]  + frustumMatrix[8];
	frustumPlanes[LEFT].w = frustumMatrix[15]  + frustumMatrix[12];

	frustumPlanes[RIGHT].x = frustumMatrix[3]   - frustumMatrix[0];
	frustumPlanes[RIGHT].y = frustumMatrix[7]   - frustumMatrix[4];
	frustumPlanes[RIGHT].z = frustumMatrix[11]  - frustumMatrix[8];
	frustumPlanes[RIGHT].w = frustumMatrix[15]  - frustumMatrix[12];

	frustumPlanes[BOTTOM].x = frustumMatrix[3]   + frustumMatrix[1];
	frustumPlanes[BOTTOM].y = frustumMatrix[7]   + frustumMatrix[5];
	frustumPlanes[BOTTOM].z = frustumMatrix[11]  + frustumMatrix[9];
	frustumPlanes[BOTTOM].w = frustumMatrix[15]  + frustumMatrix[13];

	frustumPlanes[TOP].x = frustumMatrix[3]   - frustumMatrix[1];
	frustumPlanes[TOP].y = frustumMatrix[7]   - frustumMatrix[5];
	frustumPlanes[TOP].z = frustumMatrix[11]  - frustumMatrix[9];
	frustumPlanes[TOP].w = frustumMatrix[15]  - frustumMatrix[13];

	frustumPlanes[FRONT].x = frustumMatrix[3]   + frustumMatrix[2];
	frustumPlanes[FRONT].y = frustumMatrix[7]   + frustumMatrix[6];
	frustumPlanes[FRONT].z = frustumMatrix[11]  + frustumMatrix[10];
	frustumPlanes[FRONT].w = frustumMatrix[15]  + frustumMatrix[14];

	frustumPlanes[BACK].x = frustumMatrix[3]   - frustumMatrix[2];
	frustumPlanes[BACK].y = frustumMatrix[7]   - frustumMatrix[6];
	frustumPlanes[BACK].z = frustumMatrix[11]  - frustumMatrix[10];
	frustumPlanes[BACK].w = frustumMatrix[15]  - frustumMatrix[14];


	for (int i=0; i<6; i++)
		frustumPlanes[i].Normalize();

}

bool crFrustum::isPointInside(crVec3 point) {

	for (int i=0; i<6; i++) {
		if (frustumPlanes[i].x * point.x + 
			frustumPlanes[i].y * point.y +
			frustumPlanes[i].z * point.z +
			frustumPlanes[i].w <= - EPSILON) return false;
	}

	return true;
}

bool crFrustum::isSphereInside(crVec3 point, float radius) {
	for (int i=0; i<6; i++) {
		if (frustumPlanes[i].x * point.x + 
			frustumPlanes[i].y * point.y +
			frustumPlanes[i].z * point.z +
			frustumPlanes[i].w < -radius) return false;
	}

	return true;
}

bool crFrustum::isAABBInside(crAABB& bounds) {
	int outVert = 0;
	crVec3 vertices[8] = { bounds.min, 
						  crVec3(bounds.min.x, bounds.min.y, bounds.max.z),
						  crVec3(bounds.min.x, bounds.max.y, bounds.max.z),
						  crVec3(bounds.min.x, bounds.max.y, bounds.min.z),
						  crVec3(bounds.max.x, bounds.max.y, bounds.min.z),
						  crVec3(bounds.max.x, bounds.min.y, bounds.min.z),
						  crVec3(bounds.max.x, bounds.min.y, bounds.max.z),
						  bounds.max										};

	for(int a=0; a<6; a++) {
		outVert = 0;
		for(int v=0; v<8; v++)  {
				if (frustumPlanes[a].x * vertices[v].x + 
					frustumPlanes[a].y * vertices[v].y +
					frustumPlanes[a].z * vertices[v].z +
					frustumPlanes[a].w <= - EPSILON) outVert++;
		}

		bounds.PointsVisible = outVert;
		if (outVert==8) return false;
	}
						
	return true;
}