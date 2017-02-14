#include "matrix.h"

/*=========
    crMat2
  =========*/
crMat2::crMat2() {
	setIdentity();
}

crMat2::crMat2	(float m11,	float m12,
			 float m21, float m22 ) {
	_mat[0] = m11;
	_mat[1] = m21;
	_mat[2] = m12;
	_mat[3] = m22;
}

crMat2::crMat2(float mat[4]) {
	*this->_mat = *mat;
}

//==============
// crMat2::operator[]
//==============
float&	crMat2::operator[]		(int i) {
	static float err = 0;
	return (i<4 && i>-1)? _mat[i] : err;
}

//==============
// crMat2::operator+
//==============
crMat2	crMat2::operator+		(const crMat2 &mat) {
	crMat2 m = crMat2(mat._mat[0] + _mat[0],    mat._mat[2] + _mat[2],
				  mat._mat[1] + _mat[1],    mat._mat[3] + _mat[3] );

	return m;

}

//==============
// crMat2::operator-
//==============
crMat2	crMat2::operator-		(const crMat2 &mat) {
	crMat2 m = crMat2(mat._mat[0] - _mat[0],    mat._mat[2] - _mat[2],
				  mat._mat[1] - _mat[1],    mat._mat[3] - _mat[3] );

	return m;
}

//==============
// crMat2::operator* (crMat2)
//==============
crMat2	crMat2::operator*		(const crMat2 &mat) {
	crMat2 m;
	m._mat[0] = _mat[0] * mat._mat[0] + _mat[2] * mat._mat[1];
	m._mat[1] = _mat[0] * mat._mat[2] + _mat[2] * mat._mat[3];
	m._mat[2] = _mat[1] * mat._mat[0] + _mat[3] * mat._mat[1];
	m._mat[3] = _mat[1] * mat._mat[2] + _mat[3] * mat._mat[3];

	return m;
}

//==============
// crMat2::operator* (float)
//==============
crMat2	crMat2::operator*		(const float scalar) {
	crMat2 m = crMat2(_mat[0] * scalar,    _mat[2] * scalar,
					  _mat[1] * scalar,    _mat[3] * scalar );

	return m;
}

//==============
// crMat2::Transpose
//==============
crMat2	crMat2::Transpose() const {
	crMat2 transpose = crMat2(_mat[0], _mat[1],
						  _mat[2], _mat[3]);
	return transpose;
}

//==============
// crMat2::Adjung
//==============
crMat2	crMat2::Adjung() const {
	crMat2 adjung;
	adjung._mat[0] =   _mat[3];
	adjung._mat[1] = - _mat[2];
	adjung._mat[2] = - _mat[1];
	adjung._mat[3] =   _mat[0];

	return adjung;
}

//==============
// crMat2::Inverse
//==============
crMat2	crMat2::Inverse() const {
	crMat2 mat = Adjung() * (1/Determinant());
	return mat.Transpose();
}

//==============
// crMat2::Determinant
//==============
float	crMat2::Determinant() const {
	float det = (_mat[0]*_mat[3] + _mat[2]*_mat[1]) -
				(_mat[2]*_mat[1] + _mat[1]*_mat[3]);
	return det;
}

//==============
// crMat2::TocrMat3
//==============
crMat3	crMat2::ToMat3() {
	return crMat3(_mat[0], _mat[2], 0,
		        _mat[1], _mat[3], 0,
		  			  0,       0, 1 );
}

//==============
// crMat2::TocrMat4
//==============
crMat4	crMat2::ToMat4() {
	return crMat4(_mat[0], _mat[2], 0, 0,
		          _mat[1], _mat[3], 0, 0,
		  			  0,         0, 1, 0,
		              0,         0, 0, 1 );
}

//==============
// crMat2::setInverse
//==============
void	crMat2::setInverse() {
	*_mat = *Inverse()._mat;
}

//==============
// crMat2::setTranspose
//==============
void	crMat2::setTranspose		() {
	*_mat = *Transpose()._mat;
}


//==============
// crMat2::setIdentity
//==============
void	crMat2::setIdentity		() {
	_mat[0] = 1;		_mat[2] = 0;
	_mat[1] = 0;		_mat[3] = 1;
}

//==============
// crMat2::setAdjung
//==============
void	crMat2::setAdjung			() {
	*_mat = *Adjung()._mat;
}

//==============
// crMat2::IsIdentity
//==============
bool	crMat2::IsIdentity		(){
	crMat2 Diagonal;
	Diagonal.setIdentity();
	return (*_mat == *Diagonal._mat)? true : false;
}

//==============
// crMat2::IsProjective
//==============
bool	crMat2::IsProjective		() {
	crMat2 projective;
	projective = *this * *this;
	return (*_mat == *projective._mat)? true : false;
}

//==============
// crMat2::Rotate
//==============
void	crMat2::Rotate( float angle ) {
	float cosT = cosf(angle),
		  sinT = sinf(angle);
	*this = (*this) * crMat2 (cosT, -sinT,
							sinT,  cosT );
				  
}

float* crMat2::ToFloatPtr( void ) {
	return ( &_mat[0] );
}

/*=========
    crMat3
  =========*/

crMat3::crMat3(void) {
	setIdentity();
}

crMat3::crMat3(float m11, float m21, float m31, 
		   float m12, float m22, float m32, 
		   float m13, float m23, float m33) {
	_mat[0] = m11;			_mat[3] = m12;				_mat[6] = m13;
	_mat[1] = m21;			_mat[4] = m22;				_mat[7] = m23;
	_mat[2] = m31;			_mat[5] = m32;				_mat[8] = m33;
}

crMat3::crMat3(float mat[]) {
	*_mat = *mat;
}

//==============
// crMat3::Operator []
//==============
float&   crMat3::operator[](int i) {
	 static float e = 0.0f;
	return ( (i<0) || (i>8))? e  : _mat[i];
}

//==============
// crMat3::Operator +
//==============
crMat3	crMat3::operator+ (const crMat3 &m) {
	crMat3 mat;
	for (int i=0; i<9; i++)
		mat._mat[i] = _mat[i] + m._mat[i];
	return mat;
}


//==============
// crMat3::Operator -
//==============
crMat3	crMat3::operator- (const crMat3 &m) {
	crMat3 mat;
	for (int i=0; i<9; i++)
		mat._mat[i] = _mat[i] - m._mat[i];

	return mat;
}

//==============
// crMat3::Operator *(crMat3)
//==============
crMat3	crMat3::operator* (const crMat3 &m) {
	crMat3 mat;

	mat[0] = m._mat[0] * _mat[0] + m._mat[3] * _mat[1] + m._mat[6] * _mat[2]; 
	mat[1] = m._mat[1] * _mat[0] + m._mat[4] * _mat[1] + m._mat[7] * _mat[2]; 
	mat[2] = m._mat[2] * _mat[0] + m._mat[5] * _mat[1] + m._mat[8] * _mat[2]; 

	mat[3] = m._mat[0] * _mat[3] + m._mat[3] * _mat[4] + m._mat[6] * _mat[5]; 
	mat[4] = m._mat[1] * _mat[3] + m._mat[4] * _mat[4] + m._mat[7] * _mat[5]; 
	mat[5] = m._mat[2] * _mat[3] + m._mat[5] * _mat[4] + m._mat[8] * _mat[5]; 

	mat[6] = m._mat[0] * _mat[6] + m._mat[3] * _mat[7] + m._mat[6] * _mat[8]; 
	mat[7] = m._mat[1] * _mat[6] + m._mat[4] * _mat[7] + m._mat[7] * _mat[8]; 
	mat[8] = m._mat[2] * _mat[6] + m._mat[5] * _mat[7] + m._mat[8] * _mat[8]; 

	return mat;
}

//==============
// crMat3::Operator *(scalar)
//==============
crMat3 crMat3::operator* (const float s) {
	crMat3 mat;
	for (int i=0; i<9; i++)
		mat._mat[i] = _mat[i] * s;

	return mat;	
}

//==============
// crMat3::Operator *(crVec3)
//==============
crVec3 crMat3::operator *(const crVec3 v) {
	return crVec3(  _mat[0] * v.x + _mat[3] * v.y + _mat[6]  * v.z,
				  _mat[1] * v.x + _mat[4] * v.y + _mat[7]  * v.z ,
				  _mat[2] * v.x + _mat[5] * v.y + _mat[8]  * v.z    );
}

//==============
// crMat3::Transpose
//==============
crMat3	crMat3::Transpose() const {
	crMat3 trans;

	trans[0] = _mat[0];
	trans[1] = _mat[3];
	trans[2] = _mat[6];

	trans[3] = _mat[1];
	trans[4] = _mat[4];
	trans[5] = _mat[7];

	trans[6] = _mat[2];
	trans[7] = _mat[5];
	trans[8] = _mat[8];

	return trans;
}

//==============
// crMat3::Inverse
//==============
crMat3	crMat3::Inverse() const {
	crMat3 mat = Adjung() * (1/Determinant());
	return mat.Transpose();
}

//==============
// crMat3::Determinant
//==============
float crMat3::Determinant() const {
	return (_mat[0]  *  _mat[4] * _mat[8] + 
			_mat[3]  *  _mat[7] * _mat[2] + 
			_mat[6]  *  _mat[1] * _mat[5]   ) 
		                  - 
		   (_mat[6]  *  _mat[4] * _mat[2] + 
			_mat[3]  *  _mat[1] * _mat[8] + 
			_mat[0]  *  _mat[7] * _mat[5]   );
}

//==============
// crMat3::Adjung
//==============
crMat3 crMat3::Adjung() const {
	crMat3	adjung;
	float	det[9];

	det[0] = crMat2(_mat[4], _mat[7], _mat[5], _mat[8]).Determinant();
	det[1] = crMat2(_mat[3], _mat[6], _mat[5], _mat[8]).Determinant();
	det[2] = crMat2(_mat[3], _mat[6], _mat[4], _mat[7]).Determinant();

	det[3] = crMat2(_mat[1], _mat[7], _mat[2], _mat[8]).Determinant();
	det[4] = crMat2(_mat[0], _mat[6], _mat[2], _mat[8]).Determinant();
	det[5] = crMat2(_mat[0], _mat[6], _mat[1], _mat[7]).Determinant();

	det[6] = crMat2(_mat[1], _mat[4], _mat[2], _mat[5]).Determinant();
	det[7] = crMat2(_mat[0], _mat[3], _mat[2], _mat[5]).Determinant();
	det[8] = crMat2(_mat[0], _mat[3], _mat[1], _mat[4]).Determinant();

	adjung = crMat3 ( det[0],   -det[0],    det[0],
				   -det[0],    det[0],   -det[0],
					det[0],   -det[0],    det[0] );

	return adjung;
}

//==============
// crMat3::setTranspose
//==============
void	crMat3::setTranspose() {
	*_mat = *Transpose()._mat;
}

//==============
// crMat3::setInverse
//==============
void	crMat3::setInverse() {
	*_mat = *Inverse()._mat;
}

//==============
// crMat3::setIdentity
//==============
void	crMat3::setIdentity() {
//	crMat3 mat = crMat3(1,0,0,
//			   		0,1,0,
//					0,0,1);
	*_mat = *crMat3(1,0,0,
			   	  0,1,0,
				  0,0,1)._mat;
}

//==============
// crMat3::setAdjung
//==============
void	crMat3::setAdjung() {
	*_mat = *Adjung()._mat;
}

//==============
// crMat3::IsProjective
//==============
bool	crMat3::IsProjective() {
	//crMat3 sqr_mat = *this * *this;
	return (*(*this * *this)._mat == *_mat)? true : false;
}

//==============
// crMat3::IsIdentity
//==============
bool crMat3::IsIdentity() {
	crMat3 Diagonal_mat;
	Diagonal_mat.setIdentity();
	return (*_mat == *Diagonal_mat._mat)? true : false;
}

//==============
// crMat3::TocrMat4
//==============
crMat4	crMat3::ToMat4() {
	return crMat4(_mat[0], _mat[3], _mat[6], 0, 
				_mat[1], _mat[4], _mat[7], 0,
				_mat[2], _mat[5], _mat[8], 0, 
				0,		0,		 0,		   1  );
}

//==============
// crMat3::Rotate()
//==============
void crMat3::Rotate(float x, float y, float z) {
	float XsinT = sinf( x ),
		  XcosT = cosf( x ),
		  YsinT = sinf( y ),
		  YcosT = cosf( y ),
		  ZsinT = sinf( z ),
		  ZcosT = cosf( z );

	crMat3 rotx = crMat3( 1,	0,		0,
					  0,   XcosT, -XsinT,
					  0,   XsinT,  XcosT );

	crMat3 roty = crMat3( YcosT,	0,		YsinT,
						0,		1,		  0,
					 -YsinT,	0,		YcosT);

	crMat3 rotz = crMat3( ZcosT, -ZsinT,	0,
					  ZsinT,  ZcosT,	0,
					    0,		0,		1  );
	*this =   (rotx * roty * rotz); 
}

float* crMat3::ToFloatPtr( void ) {
	return ( &_mat[0] );
}

/*==============
    crMat4
  ==============*/

crMat4::crMat4(void) {
	setIdentity();
}

crMat4::crMat4(float m11,	 float m12,  float m13,	 float m14,
   		   float m21,	 float m22,  float m23,	 float m24,
		   float m31,	 float m32,  float m33,	 float m34,
		   float m41,	 float m42,  float m43,	 float m44) {
	_mat[0] = m11;	_mat[4] = m12;	_mat[8]  = m13;	_mat[12] = m14;
	_mat[1] = m21;	_mat[5] = m22;	_mat[9]  = m23;	_mat[13] = m24;
	_mat[2] = m31;	_mat[6] = m32;	_mat[10] = m33;	_mat[14] = m34;
	_mat[3] = m41;	_mat[7] = m42;	_mat[11] = m43;	_mat[15] = m44;
}

crMat4::crMat4(float mat[]) {
	*_mat = *mat;
}

//==============
// crMat4::operator+
//==============
crMat4	crMat4::operator+	(const crMat4& m) {
	crMat4 mat;
	for(int i=0; i<16; i++) {
		mat[i] = m._mat[i] + this->_mat[i];
	}
	return mat;
}

//==============
// crMat4::operator-
//==============
crMat4	crMat4::operator-	(const crMat4& m) {
	crMat4 mat;
	for(int i=0; i<16; i++) {
		mat[i] = m._mat[i] - this->_mat[i];
	}
	return mat;
}

//==============
// crMat4::operator/ <-- not completed -->
//==============
crMat4	crMat4::operator/	(const crMat4& m) {
	crMat4 mat;
/*******************************/
	return mat;
}

//==============
// crMat4::operator[]
//==============
float&	crMat4::operator[](int i) {
    static float e = 0.0f;
	return ( (i<0) || (i>15))? e  : _mat[i];
}

//==============
// crMat4::operator*(crMat4)
//==============
crMat4	crMat4::operator*	(const crMat4 &m) {
	crMat4 mat;

	mat[0]  = _mat[0] * m._mat[0]  + _mat[4] * m._mat[1]  + _mat[8]  * m._mat[2] + _mat[12] * m._mat[3];
	mat[1]  = _mat[1] * m._mat[0]  + _mat[5] * m._mat[1]  + _mat[9]  * m._mat[2] + _mat[13] * m._mat[3];
	mat[2]  = _mat[2] * m._mat[0]  + _mat[6] * m._mat[1]  + _mat[10] * m._mat[2] + _mat[14] * m._mat[3];
	mat[3]  = _mat[3] * m._mat[0]  + _mat[7] * m._mat[1]  + _mat[11] * m._mat[2] + _mat[15] * m._mat[3];

	mat[4]  = _mat[0] * m._mat[4]  + _mat[4] * m._mat[5] + _mat[8]  * m._mat[6] + _mat[12] * m._mat[7];
	mat[5]  = _mat[1] * m._mat[4]  + _mat[5] * m._mat[5] + _mat[9]  * m._mat[6] + _mat[13] * m._mat[7];
	mat[6]  = _mat[2] * m._mat[4]  + _mat[6] * m._mat[5] + _mat[10] * m._mat[6] + _mat[14] * m._mat[7];
	mat[7]  = _mat[3] * m._mat[4]  + _mat[7] * m._mat[5] + _mat[11] * m._mat[6] + _mat[15] * m._mat[7];

	mat[8]  = _mat[0] * m._mat[8]  + _mat[4] * m._mat[9] + _mat[8]  * m._mat[10] + _mat[12] * m._mat[11];
	mat[9]  = _mat[1] * m._mat[8]  + _mat[5] * m._mat[9] + _mat[9]  * m._mat[10] + _mat[13] * m._mat[11];
	mat[10] = _mat[2] * m._mat[8]  + _mat[6] * m._mat[9] + _mat[10] * m._mat[10] + _mat[14] * m._mat[11];
	mat[11] = _mat[3] * m._mat[8]  + _mat[7] * m._mat[9] + _mat[11] * m._mat[10] + _mat[15] * m._mat[11];

	mat[12] = _mat[0] * m._mat[12] + _mat[4] * m._mat[13] + _mat[8]  * m._mat[14] + _mat[12] * m._mat[15];
	mat[13] = _mat[1] * m._mat[12] + _mat[5] * m._mat[13] + _mat[9]  * m._mat[14] + _mat[13] * m._mat[15];
	mat[14] = _mat[2] * m._mat[12] + _mat[6] * m._mat[13] + _mat[10] * m._mat[14] + _mat[14] * m._mat[15];
	mat[15] = _mat[3] * m._mat[12] + _mat[7] * m._mat[13] + _mat[11] * m._mat[14] + _mat[15] * m._mat[15];

	return mat;
}

//==============
// crMat4::operator*(float)
//==============
crMat4 crMat4::operator* (const float s) {
	crMat4 mat;
	for (int i=0; i<15; i++)
		mat._mat[i] = _mat[i] * s;

	return mat;	
}

//==============
// crMat4::operator*(crVec4)
//==============
crVec4	crMat4::operator*(const crVec4 v){
	return crVec4( _mat[0] * v.x + _mat[4] * v.y + _mat[8]  * v.z + _mat[12] * v.w,
				  _mat[1] * v.x + _mat[5] * v.y + _mat[9]  * v.z + _mat[13] * v.w,
				  _mat[2] * v.x + _mat[6] * v.y + _mat[10] * v.z + _mat[14] * v.w,
				  _mat[3] * v.x + _mat[7] * v.y + _mat[11] * v.z + _mat[15] * v.w  );
}

//==============
// crMat4::Transpose
//==============
crMat4	crMat4::Transpose	() const{
	crMat4 mat = crMat4( _mat[0],	_mat[1],	_mat[2],	_mat[3],
					 _mat[4],	_mat[5],	_mat[6],	_mat[7], 
					 _mat[8],	_mat[9],	_mat[10],	_mat[11], 
					 _mat[12],	_mat[13],	_mat[14],   _mat[15] );
	return mat;
}

//==============
// crMat4::Inverse
//==============
crMat4	crMat4::Inverse() const {
	crMat4 mat = Adjung() * (1/Determinant());
	return mat.Transpose();
}

//==============
// crMat4::Determinant
//==============
float crMat4::Determinant() const{
	return (_mat[0]  * _mat[5]  * _mat[10] * _mat[15] + 
		    _mat[4]  * _mat[9]  * _mat[14] * _mat[3]  +
			_mat[8]  * _mat[13] * _mat[2]  * _mat[7]  +
			_mat[12] * _mat[1]  * _mat[6]  * _mat[11]   ) 
			                   -
		   (_mat[12] * _mat[9]  * _mat[6]  * _mat[3]  + 
		    _mat[8]  * _mat[5]  * _mat[2]  * _mat[15] +
			_mat[4]  * _mat[1]  * _mat[14] * _mat[11] +
			_mat[0]  * _mat[13] * _mat[10] * _mat[7]		);
}


//==============
// crMat4::Adjung
//==============
crMat4	crMat4::Adjung() const{
	crMat4	adjung;
	float	det[16];

	det[0]  =  crMat3(  _mat[5],    _mat[9],    _mat[13],
					  _mat[6],    _mat[10],   _mat[14],
					  _mat[7],    _mat[11],   _mat[15] ).Determinant();

	det[1]  =  crMat3(  _mat[4],    _mat[8],    _mat[12],
					  _mat[6],    _mat[10],   _mat[14],
					  _mat[7],    _mat[11],   _mat[15] ).Determinant();

	det[2]  =  crMat3(  _mat[4],    _mat[8],    _mat[12],
					  _mat[5],    _mat[9],    _mat[13],
					  _mat[7],    _mat[11],   _mat[15] ).Determinant();

	det[3]  =  crMat3(  _mat[4],    _mat[8],    _mat[12],
					  _mat[5],    _mat[9],    _mat[13],
					  _mat[6],    _mat[10],   _mat[14] ).Determinant();

	det[4]  =  crMat3(  _mat[1],    _mat[9],     _mat[13],
					  _mat[2],    _mat[10],    _mat[14],
					  _mat[3],    _mat[11],    _mat[15] ).Determinant();

	det[5]  =  crMat3(  _mat[0],    _mat[8],    _mat[12],
					  _mat[2],    _mat[10],   _mat[14],
					  _mat[3],    _mat[11],   _mat[15] ).Determinant();

	det[6]  =  crMat3(  _mat[0],    _mat[8],    _mat[12],
					  _mat[1],    _mat[9],    _mat[13],
					  _mat[3],    _mat[11],   _mat[15] ).Determinant();

	det[7]  =  crMat3(  _mat[0],    _mat[8],    _mat[12],
					  _mat[1],    _mat[9],    _mat[13],
					  _mat[2],    _mat[10],   _mat[14] ).Determinant();

	det[8]  =  crMat3(  _mat[1],    _mat[5],    _mat[13],
					  _mat[2],    _mat[6],    _mat[14],
					  _mat[3],    _mat[7],    _mat[15] ).Determinant();

	det[9]  =  crMat3(  _mat[0],    _mat[4],    _mat[12],
					  _mat[2],    _mat[6],    _mat[14],
					  _mat[3],    _mat[7],    _mat[15] ).Determinant();

	det[10] =  crMat3(  _mat[0],    _mat[4],    _mat[12],
					  _mat[1],    _mat[5],    _mat[13],
					  _mat[3],    _mat[7],    _mat[15] ).Determinant();

	det[11] =  crMat3(  _mat[0],    _mat[4],    _mat[12],
					  _mat[1],    _mat[5],    _mat[13],
					  _mat[2],    _mat[6],    _mat[14] ).Determinant();

	det[12] =  crMat3(  _mat[1],    _mat[5],    _mat[9],
					  _mat[2],    _mat[6],    _mat[10],
					  _mat[3],    _mat[7],    _mat[11] ).Determinant();

	det[13] =  crMat3(  _mat[0],    _mat[4],    _mat[8],
					  _mat[2],    _mat[6],    _mat[10],
					  _mat[3],    _mat[7],    _mat[11] ).Determinant();

	det[14] =  crMat3(  _mat[0],    _mat[4],    _mat[8],
					  _mat[1],    _mat[5],    _mat[9],
					  _mat[3],    _mat[7],    _mat[11] ).Determinant();

	det[15] =  crMat3(  _mat[0],    _mat[4],    _mat[8],
					  _mat[1],    _mat[5],    _mat[9],
					  _mat[2],    _mat[6],    _mat[10] ).Determinant();

	adjung = crMat4(
			det[0],   -det[4],    det[8],    -det[12],
		   -det[1],    det[5],   -det[9],     det[13],
		    det[2],   -det[6],    det[10],   -det[14],
		   -det[3],    det[7],   -det[11],    det[15]
	);

	return adjung;
}

//==============
// crMat4::setTranspose
//==============
void	crMat4::setTranspose() {
	*_mat = *Transpose()._mat;
}

//==============
// crMat4::setInverse
//==============
void	crMat4::setInverse() {
	*_mat = *Inverse()._mat;
}

//==============
// crMat4::setIdentity
//==============
void	crMat4::setIdentity() {
	crMat4 mat = crMat4(1,0,0,0,
			   		0,1,0,0,
					0,0,1,0,
					0,0,0,1 );
	*this = mat;
}

//==============
// crMat4::setAdjung
//==============
void	crMat4::setAdjung() {
	*_mat = *Adjung()._mat;
}

//==============
// crMat4::IsProjective
//==============
bool crMat4::IsProjective() {
	crMat4 sqr_mat = *this * *this;

	return (*sqr_mat._mat == *_mat)? true : false;
}

//==============
// crMat4::IsIdentity
//==============
bool crMat4::IsIdentity() {
	crMat4 Diagonal_mat;
	Diagonal_mat.setIdentity();
	return (*_mat == *Diagonal_mat._mat)? true : false;
}

//==============
// crMat4::Scale
//==============
void crMat4::Scale(float x, float y, float z)  {
	_mat[0] = x;
	_mat[5] = y;
	_mat[10] = z;
}

//==============
// crMat4::Translate
//==============
void crMat4::Translate(float x, float y, float z) {
	crMat4 trans = crMat4(1, 0, 0, x,
					  0, 1, 0, y,
					  0, 0, 1, z,
					  0, 0, 0, 1  );
	*this = *this * trans;
}

//==============
// crMat4::Translate
//==============
void crMat4::Translate(crVec3 pos) {
	Translate(pos.x, pos.y, pos.z);
}

//==============
// crMat4::Rotate
//==============
void crMat4::Rotate (float x, float y, float z) {
	
	crMat4 rotX = crMat4(
					1,	0,			0,	  0,
					0, cosf(x), -sinf(x), 0,
					0, sinf(x),  cosf(x), 0,
					0,	0,			0,	  1
				);

	crMat4 rotY = crMat4(
					cosf(y),    0,    sinf(y),	0,
						0,		1,		 0,		0,
				   -sinf(y),    0,    cosf(y),  0,
						0,		0,		 0,		1
				);

	crMat4 rotZ = crMat4(
					cosf(z),	 -sinf(z),	0, 0,
					sinf(z),	cosf(z),	0, 0,
					0,				0,		1, 0,
					0,				0,		0, 1
				);
	*this =  (rotX * rotY * rotZ);
}

float* crMat4::ToFloatPtr( void ) {
	return ( &_mat[0] );
}

crMat3 crMat4::ToMat3( void ) {
	return crMat3( _mat[0], _mat[4], _mat[8],
				   _mat[1], _mat[5], _mat[9],
				   _mat[2], _mat[6], _mat[10] );
}