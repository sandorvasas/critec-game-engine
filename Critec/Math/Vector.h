// Copyright (C) 2006-2007 by Sandor Vasas
//
#ifndef __CRITEC_VECTOR_H_	
#define __CRITEC_VECTOR_H_

//#include "Matrix.h"
#include <math.h>
#include <stdio.h>

#ifndef __PI__
#define __PI__
 const float PI = 3.1415926535f;
#endif

class crVec2;
class crVec3;
class crVec4;

//======================
// crVec2 class
//======================
class crVec2 {
public:
	float x, y;

public:
				crVec2( void );
	explicit	crVec2( float x, float y );
	
	float&		operator []( int index );
	crVec2		operator =( const crVec2& v );
	bool		operator ==( const crVec2& v );
	crVec2		operator -( void ) const;
	crVec2		operator -( const crVec2& v ) const;
	crVec2		operator -( const float& s ) const;
	crVec2		operator -=( crVec2 v );
	crVec2		operator -=( float s );
	crVec2		operator *( const crVec2& v ) const;
	crVec2		operator *( const float& s) const;
	crVec2		operator *=( crVec2 v );
	crVec2		operator *=( float s );
	crVec2		operator /( const crVec2& v ) const;
	crVec2		operator /( const float& s) const;
	crVec2		operator /=( crVec2 v );
	crVec2		operator /=( float s );
	crVec2		operator +( const crVec2& v ) const;
	crVec2		operator +( const float& s) const;
	crVec2		operator +=	( crVec2 v );
	crVec2		operator +=( float s );
	bool		operator >=( const crVec2& v) const;
	bool		operator <=( const crVec2& v) const;
	bool		operator >( const crVec2& v) const;
	bool		operator <( const crVec2& v) const;

	crVec2		GetOrtho( void );

	void		Rotate( float angle );
	void		Translate( float x, float y );

	float*		ToFloatPtr( void );
	char*		ToCharPtr( void );

	float		Length( void );
	//crVec2		Absolute( void );
	void		Normalize( void );
/*	crVec2		Cross( crVec2 v1, crVec2 v2 );
	crVec2		Lerp( crVec2 v1, crVec2 v2, float f );
*/
};

//======================
// crVec3 class
//======================
class crVec3 {
public:
	float x, y, z;

public:
				crVec3( void );
	explicit	crVec3( float x, float y, float z );
	explicit	crVec3( crVec2 v, float z );
	
	float&		operator []( int index );
	 crVec3		operator =( const crVec3& v );
	 bool		operator ==( const crVec3& v );
	 crVec3		operator -( void ) const;
	 crVec3		operator -( const crVec3& v ) const;
	 crVec3		operator -( const float& s ) const;
	 crVec3		operator -=( crVec3 v );
	 crVec3		operator -=( float s );
	 crVec3		operator *( const crVec3& v ) const;
	 crVec3		operator *( const float& s) const;
	 crVec3		operator *=( crVec3 v );
	 crVec3		operator *=( float s );
	 crVec3		operator /( const crVec3& v ) const;
	 crVec3		operator /( const float& s) const;
	 crVec3		operator /=( crVec3 v );
	 crVec3		operator /=( float s );
	 crVec3		operator +( const crVec3& v ) const;
	 crVec3		operator +( const float& s) const;
	 crVec3		operator +=( crVec3 v );
	 crVec3		operator +=( float s );
	 bool		operator >=( const crVec3& v) const;
	 bool		operator <=( const crVec3& v) const;
	 bool		operator >( const crVec3& v) const;
	 bool		operator <( const crVec3& v) const;

	crVec3		GetOrthoXY( void );
	crVec3		GetOrthoXZ( void );
	crVec3		GetOrthoYZ( void );

	void		Rotate( float x, float y, float z );
	void		Translate( float x, float y, float z );

	float*		ToFloatPtr( void );
	char*		ToCharPtr( void );

	float		Length( void );
	//crVec3		Absolute( void );
	void		Normalize( void );
	/*crVec3		Cross( crVec3 v1, crVec3 v2 );
	crVec3		Lerp( crVec3 v1, crVec3 v2, float f );*/
};


//======================
// crVec4 class
//======================
class crVec4 : public crVec3 {
public:
	float x, y, z, w;

public:
				crVec4( void );
	explicit	crVec4( float x, float y, float z, float w );
	explicit	crVec4( crVec2 v, float z, float w );
	explicit	crVec4( crVec3 v, float w );
	
	float&		operator []( int index );
	crVec4		operator =( const crVec4& v );
	bool		operator ==( const crVec4& v );
	crVec4		operator -( void ) const;
	crVec4		operator -( const crVec4& v ) const;
	crVec4		operator -( const float& s ) const;
	crVec4		operator -=( crVec4 v );
	crVec4		operator -=( float s );
	crVec4		operator *( const crVec4& v ) const;
	crVec4		operator *( const float& s) const;
	crVec4		operator *=( crVec4 v );
	crVec4		operator *=( float s );
	crVec4		operator /( const crVec4& v ) const;
	crVec4		operator /( const float& s) const;
	crVec4		operator /=( crVec4 v );
	crVec4		operator /=( float s );
	crVec4		operator +( const crVec4& v ) const;
	crVec4		operator +( const float& s) const;
	crVec4		operator +=( crVec4 v );
	crVec4		operator +=( float s );
	bool		operator >=( const crVec4& v) const;
	bool		operator <=( const crVec4& v) const;
	bool		operator >( const crVec4& v) const;
	bool		operator <( const crVec4& v) const;

	float*		ToFloatPtr( void );
	char*		ToCharPtr( void );

	float		Length( void );
	//crVec4		Absolute( void );
	void		Normalize( void );
	/*crVec4		Cross( crVec4 v1, crVec4 v2 );
	crVec4		Lerp( crVec4 v1, crVec4 v2, float f );*/
};


//==============================
//     Vector Functions
//==============================
crVec2	normalize( crVec2& );
crVec2	abs( crVec2 );
float	dot( crVec2, crVec2 );
float	cross( crVec2, crVec2 );
crVec2	lerp( crVec2, crVec2, float );

crVec3	normalize( crVec3& );
crVec3	abs( crVec3 );
float	dot( crVec3, crVec3 );
crVec3	cross( crVec3, crVec3 );
crVec3	lerp( crVec3, crVec3, float );

crVec4	normalize( crVec4& );
crVec4	abs( crVec4 );
float	dot( crVec4, crVec4 );
crVec4	cross( crVec4, crVec4 );
crVec4	lerp( crVec4, crVec4, float );



#endif