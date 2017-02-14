#include "Vector.h"
#include "Matrix.h"

//===========================
//  crVec2 class
//===========================
crVec2::crVec2( void ) {
	x = 0.f;
	y = 0.f;
}

crVec2::crVec2( float x, float y ) {
	this->x = x;
	this->y = y;
}
	
float& crVec2::operator []( int index ) {
	static float err = 0.f;
	if (index<0 || index>1) return err;
	return ( &x )[ index ];
}

crVec2 crVec2::operator =( const crVec2& v ) {
	this->x = v.x;
	this->y = v.y;
	return *this;
}

bool crVec2::operator ==( const crVec2& v ) {
	if (this->x == v.x && this->y == v.y) return true;
	return false;
}

crVec2 crVec2::operator -( void ) const{
	return crVec2(-x, -y);
}

crVec2 crVec2::operator -( const crVec2& v ) const{
	return crVec2(x-v.x, y-v.y);
}

crVec2 crVec2::operator -( const float& s ) const{
	return crVec2(x-s, y-s);
}

crVec2 crVec2::operator -=( crVec2 v ) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

crVec2 crVec2::operator -=( float s ) {
	this->x -= s;
	this->y -= s;
	return *this;
}

crVec2 crVec2::operator *( const crVec2& v ) const {
	return crVec2(x*v.x , y*v.y);
}

crVec2 crVec2::operator *( const float& s) const {
	return crVec2(x*s , y*s);
}

crVec2 crVec2::operator *=( crVec2 v ) {
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

crVec2 crVec2::operator *=( float s ) {
	this->x *= s;
	this->y *= s;
	return *this;
}

crVec2 crVec2::operator /( const crVec2& v ) const {
	return crVec2(x/v.x , y/v.y);
}

crVec2 crVec2::operator /( const float& s) const {
	return crVec2(x/s , y/s);
}

crVec2 crVec2::operator /=( crVec2 v ) {
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

crVec2 crVec2::operator /=( float s ) {
	this->x /= s;
	this->y /= s;
	return *this;
}

crVec2 crVec2::operator +( const crVec2& v ) const {
	return crVec2(x+v.x , y+v.y);
}

crVec2 crVec2::operator +( const float& s) const {
	return crVec2(x+s , y+s);
}

crVec2 crVec2::operator +=( crVec2 v ) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

crVec2 crVec2::operator +=( float s ) {
	this->x += s;
	this->y += s;
	return *this;
}

bool crVec2::operator >=( const crVec2& v) const {
	return ( x >= v.x && y >= v.y);
}

bool crVec2::operator <=( const crVec2& v) const {
	return ( x <= v.x && y <= v.y);
}

bool crVec2::operator >( const crVec2& v) const {
	return ( x > v.x && y > v.y );
}

bool crVec2::operator <( const crVec2& v) const {
	return ( x < v.x && y < v.y );
}

crVec2 crVec2::GetOrtho( void ) {
	return crVec2(-y, x);
}

void crVec2::Rotate( float angle ) {
	crVec2 rotated;

	rotated.x  = cosf(angle) * this->x - sinf(angle) * this->y;
	rotated.y  = cosf(angle) * this->y + sinf(angle) * this->x;

	*this = rotated;
}

void crVec2::Translate( float x, float y ) {
	*this  += crVec2(x, y);
}

float* crVec2::ToFloatPtr( void ) {
	return ( &x );
}

char* crVec2::ToCharPtr( void ) {
	char* R = new char[64];
	sprintf_s(R, 64, "%5.3f/%5.3f", x, y);
	return R;
}

float crVec2::Length( void ) {
	return sqrtf( x*x + y*y );
}

//crVec2		Absolute( void );
void crVec2::Normalize( void ) {
	*this /= Length();
	//return *this;
}
/*
crVec2 crVec2::Cross( crVec2 v1, crVec2 v2 ) {
	*this =  crVec2( -y, x );

	return *this;
}

crVec2 crVec2::Lerp( crVec2 v1, crVec2 v2, float f ) {
	*this = v1*(1.0f-f) + v2*f;
	return *this;
}*/


//===========================
//  crVec3 class
//===========================
crVec3::crVec3( void ) {
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

crVec3::crVec3( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

crVec3::crVec3( crVec2 v, float z ) {
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
	
float& crVec3::operator []( int index ) {
	static float err = 0.f;
	if (index<0 || index>2) return err;
	return ( &x )[ index ];
}

crVec3 crVec3::operator =( const crVec3& v ) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

bool crVec3::operator ==( const crVec3& v ) {
	if (this->x == v.x && this->y == v.y && this->z == v.z) return true;
	return false;
}

crVec3 crVec3::operator -( void ) const{
	return crVec3(-x, -y, -z);
}

crVec3 crVec3::operator -( const crVec3& v ) const{
	return crVec3(x-v.x, y-v.y, z-v.z);
}

crVec3 crVec3::operator -( const float& s ) const{
	return crVec3(x-s, y-s, z-s);
}

crVec3 crVec3::operator -=( crVec3 v ) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

crVec3 crVec3::operator -=( float s ) {
	this->x -= s;
	this->y -= s;
	this->z -= s;
	return *this;
}

crVec3 crVec3::operator *( const crVec3& v ) const {
	return crVec3(x*v.x , y*v.y, z*v.z);
}

crVec3 crVec3::operator *( const float& s) const {
	return crVec3(x*s , y*s, z*s);
}

crVec3 crVec3::operator *=( crVec3 v ) {
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

crVec3 crVec3::operator *=( float s ) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

crVec3 crVec3::operator /( const crVec3& v ) const {
	return crVec3(x/v.x , y/v.y, z/v.z);
}

crVec3 crVec3::operator /( const float& s) const {
	return crVec3(x/s , y/s, z/s);
}

crVec3 crVec3::operator /=( crVec3 v ) {
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

crVec3 crVec3::operator /=( float s ) {
	this->x /= s;
	this->y /= s;
	this->z /= s;
	return *this;
}

crVec3 crVec3::operator +( const crVec3& v ) const {
	return crVec3(x+v.x , y+v.y, z+v.z);
}

crVec3 crVec3::operator +( const float& s) const {
	return crVec3(x+s , y+s, z+s);
}

crVec3 crVec3::operator +=( crVec3 v ) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

crVec3 crVec3::operator +=( float s ) {
	this->x += s;
	this->y += s;
	this->z += s;
	return *this;
}

bool crVec3::operator >=( const crVec3& v) const {
	return ( x >= v.x && y >= v.y && z >= v.z);
}

bool crVec3::operator <=( const crVec3& v) const {
	return ( x <= v.x && y <= v.y && z <= v.z );
}

bool crVec3::operator >( const crVec3& v) const {
	return ( x > v.x && y > v.y && z > v.z  );
}

bool crVec3::operator <( const crVec3& v) const {
	return ( x < v.x && y < v.y && z < v.z );
}


crVec3 crVec3::GetOrthoXY( void ) {
	return crVec3(-y, x, z);
}

crVec3 crVec3::GetOrthoXZ( void ) {
	return crVec3(-z, y, x);
}

crVec3 crVec3::GetOrthoYZ( void ) {
	return crVec3(x, -z, y);
}

void crVec3::Rotate( float x, float y, float z ) {
	crMat3 rot;
	rot.Rotate(x, y, z);

	*this = rot * *this ;
}

void crVec3::Translate( float x, float y, float z ) {
	*this  += crVec3(x, y, z);
}

float* crVec3::ToFloatPtr( void ) {
	return ( &x );
}

char* crVec3::ToCharPtr( void ) {
	char* R = new char[128];
	sprintf_s(R, 64, "%5.3f/%5.3f/%5.3f", x, y, z);
	return R;
}

float crVec3::Length( void ) {
	return sqrtf( x*x + y*y + z*z );
}

//crVec3		Absolute( void );
void crVec3::Normalize( void ) {
	*this /= Length();
//	return *this;
}
/*
crVec3 crVec3::Cross( crVec3 v1, crVec3 v2 ) {
	this->x = v1.y * v2.z - v1.z * v2.y;
	this->y = v1.z * v2.x - v1.x * v2.z;
	this->z = v1.x * v2.y - v1.y * v2.x;

	return *this;
}

crVec3 crVec3::Lerp( crVec3 v1, crVec3 v2, float f ) {
	*this = v1*(1.0f-f) + v2*f;
	return *this;
}*/

//===========================
//  crVec4 class
//===========================
crVec4::crVec4( void ) {
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 1.0f;
}

crVec4::crVec4( float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

crVec4::crVec4( crVec2 v, float z, float w ) {
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}

crVec4::crVec4( crVec3 v, float w ) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
	
float& crVec4::operator []( int index ) {
	static float err = 0.f;
	if (index<0 || index>3) return err;
	return ( &x )[ index ];
}

crVec4 crVec4::operator =( const crVec4& v ) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
	return *this;
}

bool crVec4::operator ==( const crVec4& v ) {
	if (	this->x == v.x 
		&&  this->y == v.y 
		&&  this->z == v.z 
		&&  this->w == v.w) return true;
	return false;
}

crVec4 crVec4::operator -( void ) const{
	return crVec4(-x, -y, -z, -w);
}

crVec4 crVec4::operator -( const crVec4& v ) const{
	return crVec4(x-v.x, y-v.y, z-v.z, w-v.w);
}

crVec4 crVec4::operator -( const float& s ) const{
	return crVec4(x-s, y-s, z-s, w-s);
}

crVec4 crVec4::operator -=( crVec4 v ) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

crVec4 crVec4::operator -=( float s ) {
	this->x -= s;
	this->y -= s;
	this->z -= s;
	this->w -= s;
	return *this;
}

crVec4 crVec4::operator *( const crVec4& v ) const {
	return crVec4(x*v.x , y*v.y, z*v.z, w*v.w);
}

crVec4 crVec4::operator *( const float& s) const {
	return crVec4(x*s , y*s, z*s,w*s);
}

crVec4 crVec4::operator *=( crVec4 v ) {
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
	return *this;
}

crVec4 crVec4::operator *=( float s ) {
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= w;
	return *this;
}

crVec4 crVec4::operator /( const crVec4& v ) const {
	return crVec4(x/v.x , y/v.y, z/v.z, w/v.w);
}

crVec4 crVec4::operator /( const float& s) const {
	return crVec4(x/s , y/s, z/s, w/s);
}

crVec4 crVec4::operator /=( crVec4 v ) {
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
	return *this;
}

crVec4 crVec4::operator /=( float s ) {
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}

crVec4 crVec4::operator +( const crVec4& v ) const {
	return crVec4(x+v.x , y+v.y, z+v.z, w+v.w);
}

crVec4 crVec4::operator +( const float& s) const {
	return crVec4(x+s , y+s, z+s, w+s);
}

crVec4 crVec4::operator +=( crVec4 v ) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

crVec4 crVec4::operator +=( float s ) {
	this->x += s;
	this->y += s;
	this->z += s;
	this->w += s;
	return *this;
}

bool crVec4::operator >=( const crVec4& v) const {
	return ( x >= v.x && y >= v.y && z >= v.z && w >= v.w );
}

bool crVec4::operator <=( const crVec4& v) const {
	return ( x <= v.x && y <= v.y && z <= v.z && w <= v.w );
}

bool crVec4::operator >( const crVec4& v) const {
	return ( x > v.x && y > v.y && z > v.z && w > v.w );
}

bool crVec4::operator <( const crVec4& v) const {
	return ( x < v.x && y < v.y && z < v.z && w < v.w );
}

float* crVec4::ToFloatPtr( void ) {
	return ( &x );
}

char* crVec4::ToCharPtr( void ) {
	char* R = new char[128];
	sprintf_s(R, 64, "%5.3f/%5.3f/%5.3f/%5.3f", x, y, z, w);
	return R;
}

float crVec4::Length( void ) {
	return sqrtf( x*x + y*y + z*z + w*w );
}

//crVec4		Absolute( void );
void crVec4::Normalize( void ) {
	*this /= Length();
	//return *this;
}
/*
crVec4 crVec4::Cross( crVec4 v1, crVec4 v2 ) {
	this->x = v1.y * v2.w - v1.w * v2.y;
	this->y = v1.z * v2.x - v1.x * v2.z;
	this->z = v1.w * v2.y - v1.y * v2.w;
	this->w = v1.x * v2.z - v1.z * v2.x;

	return *this;
}

crVec4 crVec4::Lerp( crVec4 v1, crVec4 v2, float f ) {
	*this = v1*(1.0f-f) + v2*f;
	return *this;
}*/
/*
================================================

 Functions

================================================
*/

//==================
// crVec2
//==================
crVec2 normalize(crVec2& v) {
	float m = v.Length();
	return crVec2(v.x/m, v.y/m);
}

crVec2 abs ( crVec2 v ) {
	return crVec2( fabs(v.x), fabs(v.y) );
}

float dot(crVec2 v1, crVec2 v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

float cross(crVec2 v1, crVec2 v2) {
	return (v1.y * v2.x - v1.x * v2.y); 
}

crVec2 lerp( crVec2 a, crVec2 b, float c ) {
	return (a*(1.f-c) + b*c);
}

//==================
// crVec3
//==================
crVec3 normalize(crVec3& v) {
	float m = v.Length();
	return crVec3(v.x/m, v.y/m, v.z/m);
}

crVec3 abs ( crVec3 v ) {
	return crVec3( fabs(v.x), fabs(v.y), fabs(v.z) );
}

float dot(crVec3 v1, crVec3 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

crVec3 cross(crVec3 v1, crVec3 v2) {
	return crVec3 ( v1.z * v2.y - v1.y * v2.z,
				  v1.x * v2.z - v1.z * v2.x,
				  v1.y * v2.x - v1.x * v2.y );
}

crVec3 lerp( crVec3 a, crVec3 b, float c ) {
	return (a*(1.f-c) + b*c);
}

//==================
// crVec4
//==================
crVec4 normalize(crVec4& v) {
	float m = v.Length();
	return crVec4( v.x /m, v.y/m, v.z/m, v.w/m);
}

crVec4 abs ( crVec4 v ) {
	return crVec4( fabs(v.x), fabs(v.y), fabs(v.z), fabs(v.w) );
}

float dot(crVec4 v1, crVec4 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

crVec4 cross(crVec4 v1, crVec4 v2) {
	return crVec4 ( v1.w * v2.y - v1.y * v2.w,
				  v1.x * v2.z - v1.z * v2.x,
				  v1.y * v2.w - v1.w * v2.y,
				  v1.z * v2.x - v1.x * v2.z  );

}

crVec4 lerp( crVec4 a, crVec4 b, float c ) {
	return (a*(1.f-c) + b*c);
}
