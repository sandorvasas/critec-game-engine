//   Copyright (C) 2007 by Sandor Vasas

#ifndef __CRITEC_QUATERNION_H__
#define __CRITEC_QUATERNION_H__

#include "Matrix.h"


class crQuaternion {
public:
	float x, y, z, w;
public:
	
						crQuaternion( void );
						crQuaternion( crVec3 vector, float w );
						crQuaternion( float x, float y, float z, float w );

	crQuaternion		operator+( crQuaternion q ) const;
	crQuaternion		operator-( void ) const;
	crQuaternion		operator-( crQuaternion q ) const;
	crQuaternion		operator*( crQuaternion q ) const;
	crQuaternion		operator+=( crQuaternion q );
	crQuaternion		operator-=( crQuaternion q );
	crQuaternion		operator*=( crQuaternion q );
	float&				operator[]( int i );
	bool				operator==( crQuaternion q ) const;

	void				CreateMatrix( float* Matrix ) const;
	void				CreateFromAxisAngles( float x, float y, float z, float degrees );
	void				CreateFromEulerAngles( float x, float y, float z );
};


#endif