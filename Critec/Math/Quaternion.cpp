#include "Quaternion.h"


crQuaternion::crQuaternion( void ) {
	x = 0.0; y = 0.0; z = 0.0;
	w = 1.0;
}

crQuaternion::crQuaternion	(crVec3 vector, float w) {
	this->w = w;
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

crQuaternion::crQuaternion	(float x, float y, float z, float w) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

crQuaternion crQuaternion::operator+( crQuaternion q ) const  {
	return crQuaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}

crQuaternion crQuaternion::operator-( void ) const {
	return crQuaternion(-x, -y, -z, w);
}

crQuaternion crQuaternion::operator-( crQuaternion q ) const {
	return crQuaternion(x-q.x, y-q.y, z-q.z, w-q.w);
}

crQuaternion crQuaternion::operator*( crQuaternion q ) const {
	return crQuaternion( w * q.x + q.w * x + y * q.z - z * q.y,
				  	     w * q.y + q.w * y + z * q.x - x * q.z,
					     w * q.z + q.w * z + x * q.y - y * q.x,
					     w * q.w - x * q.x - y * q.y - z * q.z);
}

crQuaternion crQuaternion::operator+=( crQuaternion q ){
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;

	return *this;
}

crQuaternion crQuaternion::operator-=( crQuaternion q ){
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;

	return *this;
}

crQuaternion crQuaternion::operator*=( crQuaternion q ){
	*this = (*this) * q;
	return *this;
}

float& crQuaternion::operator[]( int i ) {
	static float f = 0.0f;
	if (i<0 || i>4) return f;
	return ( &x ) [ i ];
}

bool crQuaternion::operator==( crQuaternion q ) const {
	return (x == q.x && y == q.y && z == q.z && w == q.w);
}

void crQuaternion::CreateFromAxisAngles( float x, float y, float z, float degrees ) {
	
	float radians = degrees * PI / 180.0f;

	float sinT = sinf( radians / 2.0f );
	
	this->w = cosf( radians / 2.0f );
	this->x = sinT * x; 
	this->y = sinT * y;
	this->z = sinT * z;
}

void crQuaternion::CreateFromEulerAngles( float x, float y, float z ) {	
	x *= PI/180.f;
	y *= PI/180.f;
	z *= PI/180.f;
	crQuaternion Qx = crQuaternion(sinf(x/2), 0.f, 0.f, cosf(x/2));
	crQuaternion Qy = crQuaternion(0.f, sinf(y/2), 0.f, cosf(y/2));
	crQuaternion Qz = crQuaternion(0.f, 0.f, sinf(z/2), cosf(z/2));

	*this = Qx * Qy * Qz;
}


void crQuaternion::CreateMatrix( float *Matrix ) const {

	if (!Matrix) return;

	Matrix[ 0] = 1.0f - 2.0f * (y * y + z * z);
	Matrix[ 1] =		2.0f * (x * y + z * w);
	Matrix[ 2] =		2.0f * (x * z - y * w);
	Matrix[ 3] = 0.f;

	Matrix[ 4] =		2.0f * (x * y - z * w);
	Matrix[ 5] = 1.0f - 2.0f * (x * x + z * z);
	Matrix[ 6] =		2.0f * (z * y + x * w);
	Matrix[ 7] = 0.0f;

	Matrix[ 8] =		2.0f * (x * z + y * w);
	Matrix[ 9] =		2.0f * (y * z - x * w);
	Matrix[10] = 1.0f - 2.0f * (x * x + y * y);
	Matrix[11] = 0.0f;

	Matrix[12] = 0.f;
	Matrix[13] = 0.f;
	Matrix[14] = 0.f;
	Matrix[15] = 1.f;
}