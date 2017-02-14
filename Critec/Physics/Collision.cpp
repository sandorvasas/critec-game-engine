#include "Collision.h"

bool crCollDetect::isPointInTriangle( crVec3 v1, crVec3 v2, crVec3 v3, crVec3 point ) {
	crVec3 p1, p2, p3;

	p1 = point - v1;
	p2 = point - v2;
	p3 = point - v3;
	p1.Normalize();
	p2.Normalize();
	p3.Normalize();

	if(fabs( acosf(dot( p1, p2 )) +
			 acosf(dot( p2, p3 )) +
			 acosf(dot( p3, p1 )) - 2*PI) <=0.005) return true;

	return false;
}

void crCollDetect::Detect_Model3ds_Camera( cr3DSModel * model, crPlayerCamera * camera ) {
	crVec3 v1, v2, v3, normal, vIntersect, lineEnd, lineStart, lineDir, offset;
	float dist, dLS, dLE, f;
	crVec3 pos = camera->Position;

	for(unsigned long obj=0; obj<model->ObjectCount; obj++) {
		for(unsigned long tri=0; tri< model->Objects[obj].Mesh->TriangleCount; tri++) {
			v1 = model->Objects[obj].Mesh->Vertices[ model->Objects[obj].Mesh->Triangles[tri].a ];
			v2 = model->Objects[obj].Mesh->Vertices[ model->Objects[obj].Mesh->Triangles[tri].b ];
			v3 = model->Objects[obj].Mesh->Vertices[ model->Objects[obj].Mesh->Triangles[tri].c ];

			normal = cross( v2 - v1, v3 - v1 );
			normal.Normalize();

			dist = -dot(normal, v1);

			for(int k=0; k<5; k++) {
				lineStart = pos + camera->boundPoints[k];
				lineEnd   = pos - camera->boundPoints[k];

				lineDir = lineEnd - lineStart;

				// get distances to plane
				dLS = dot(normal, lineStart) + dist;
				dLE = dot(normal, lineEnd) + dist;
				
				if(signum(dLS) != signum(dLE)) {
					//intersected
					f = -dLS / dot(normal, lineDir);
					vIntersect = lineStart + (lineDir * f);

					if(isPointInTriangle(v1, v2, v3, vIntersect)) {
						if(f>=0.5f)	offset = vIntersect - lineEnd;
						else		offset = vIntersect - lineStart;

						camera->Position += offset;
					//	pos = camera->Position;
					}
				}

			}
		}
	}
}


void crCollDetect::Detect_Heightmap_Camera( crHeightmap * hmap, crPlayerCamera * camera ) {
/*	crVec3 pos = camera->Position;
	crVec3 v1, v2, v3, normal, vIntersect, offset, lineEnd, lineStart, lineDir;
	float dist, dLS, dLE, offset, f;

	for(unsigned long ind = 0; ind < hmap->indices.Count; ind++) {
		v1 = hmap->vertices.Ptr()[ indices.Ptr()[ind] ];
		v1 = hmap->vertices.Ptr()[ indices.Ptr()[ind+1+hmap->] ];
		v1 = hmap->vertices.Ptr()[ indices.Ptr()[ind] ];
	}*/
}