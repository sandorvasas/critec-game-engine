#include "Vertex.h"

crVertex::crVertex( void ) {
	Clear();
}

crVertex::crVertex( const crVertex & vert) {
	this->xyz = vert.xyz;
	this->normal = vert.normal;
	this->tangent = vert.tangent;
	this->st = vert.st;

	for(int i=0; i<4; i++) {
		this->color[i] = vert.color[i];
		this->_st[i] = vert._st[i];
	}
}

crVertex::crVertex( crVec3 xyz ) {
	this-> xyz = xyz;
}

void crVertex::Clear( void ) {
	xyz = crVec3(0.0f, 0.0f, 0.0f);
	normal = crVec3(0.0f, 0.0f, 0.0f);
	tangent = crVec3(0.0f, 0.0f, 0.0f);
	st = crVec2(0.0f, 0.0f);

	for(int i=0; i<4; i++) {
		color[i] = 0;
		_st[i] = crVec2(0.0f, 0.0f);
	}
}

void crVertex::Normalize( void ) {
	xyz.Normalize();
	tangent.Normalize();
	normal.Normalize();
}

void crVertex::CalculateTangent( crVertex a, crVertex b, crVertex c ) {
	crVec3 v1, v2, pv1, pv2;
	crVec2 c1, c2;

	v1 = b.xyz - a.xyz;
	v2 = c.xyz - a.xyz;

	c1 = b.st - a.st;
	c2 = c.st - a.st;

	normal = cross( v1, v2 );
	normal.Normalize();

	pv1 = v1 - normal * dot(normal, v1);
	pv2 = v2 - normal * dot(normal, v2);

	if (c1.y + c2.x > c1.x + c2.y) {
		c1.x = -c1.x;
		c2.x = -c2.x;
	}

	tangent = (pv1 * c2.x) - (pv2 * c1.x);
	tangent.Normalize();
}

void crVertex::SetColor( int r, int g, int b ) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void crVertex::SetColor( int r, int g, int b, int a ) {
	SetColor(r, g, b);
	color[3] = a;
}

int* crVertex::GetColor( void ) const {
	return (int*)( &color[0] );
}

float* crVertex::ToFloatPtr( void ) {
	return ( xyz.ToFloatPtr() );
}