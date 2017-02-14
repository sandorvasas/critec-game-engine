#ifndef __CRITEC_MATRIX_H_
#define __CRITEC_MATRIX_H_

#include <math.h>
#include "Vector.h"

class crMat2;
class crMat3;
class crMat4;


//=============================
//	crMat2 class
//=============================
class crMat2 {
public:
	float _mat[4];

public:
					crMat2( void );
	explicit		crMat2( float m11, float m12,
						    float m21, float m22 );
	explicit		crMat2( float mat[4] );

	float&			operator[]( int i );
	crMat2			operator+( const crMat2 &mat );
	crMat2			operator-( const crMat2 &mat );
	crMat2			operator*( const crMat2 &mat );
	crMat2			operator*( const float scalar );

	crMat2			Transpose( void ) const;
	crMat2			Inverse( void ) const;
	crMat2			Adjung( void ) const;
	float			Determinant( void ) const;

	crMat3			ToMat3( void );
	crMat4			ToMat4( void );
	float*			ToFloatPtr( void );

	void			setInverse( void );
	void			setTranspose( void);
	void			setIdentity( void );
	void			setAdjung( void );

	bool			IsIdentity( void );
	bool			IsProjective( void );

	void			Rotate( float angle );

};


//========================
// crMat3 class 
//========================
class crMat3 {
public:
	float			_mat[9];

public:
					crMat3( void );
	explicit		crMat3( float m11, float m12, float m13, 
						    float m21, float m22, float m23, 
							float m31, float m32, float m33 );
	explicit		crMat3( float mat[9] );

	float&			operator[]( int i );
	crMat3			operator+( const crMat3 &m );
	crMat3			operator-( const crMat3 &m );
	crMat3			operator*( const crMat3 &m );
	crMat3			operator*( const float s );
	crVec3			operator*( const crVec3 v );

	crMat3			Transpose( void ) const;
	crMat3			Inverse( void ) const;
	crMat3			Adjung( void ) const;
	float           Determinant( void ) const;

	crMat4			ToMat4( void );
	float*			ToFloatPtr( void );

	void			setTranspose( void );
	void			setInverse( void );
	void			setIdentity( void );
	void			setAdjung( void );

	bool			IsIdentity( void );
	bool			IsProjective( void );

	void			Rotate( float x, float y, float z);
};

//========================
// crMat4 class 
//========================
class crMat4 {
public:
	float			_mat[16];

public:
					crMat4( void );
	explicit		crMat4( float m11,	float m12,  float m13,	float m14,
							float m21,	float m22,  float m23,	float m24,
							float m31,	float m32,  float m33,	float m34,
							float m41,	float m42,  float m43,	float m44 );
	explicit		crMat4( float mat[15] );

	float&			operator[]( int i); 
	crMat4			operator+( const crMat4& m );
	crMat4			operator-( const crMat4& m );
	crMat4			operator/( const crMat4& m );
	crMat4			operator*( const crMat4& m );
	crMat4			operator*( const float s );
	crVec4			operator*( const crVec4 v );

	crMat4			Transpose( void ) const;
	crMat4			Inverse( void ) const;
	crMat4			Adjung( void ) const;
	float			Determinant( void ) const;

	void			setTranspose( void );
	void			setInverse( void );
	void			setIdentity( void );
	void			setAdjung( void );

	bool			IsIdentity( void );
	bool			IsProjective( void );


	void			Scale( float x, float y, float z );
	void			Scale( crVec3 factor );
	void			Translate( float x, float y, float z );
	void			Translate( crVec3 pos );
	void			Rotate( float x, float y, float z );

	float*			ToFloatPtr( void );
	crMat3			ToMat3( void );
};

#endif