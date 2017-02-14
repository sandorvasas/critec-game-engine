// Copyright (C) 2007 by Sandor Vasas
//

/*
================================================================

	Will be a string class. 

 Bugz:
	FromLeft, FromRight, FromMiddle DOES NOT WORK.

================================================================
*/

#ifndef __CRITEC_STRING_H_
#define __CRITEC_STRING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../math/math3d.h"
#include "system.h"	//**	**//

const int STR_DEFAULT_ALLOC = 20;

class crQuaternion;
class crVec2;
class crVec3;
class crVec4;


class crStr {

private:
	char*			Text;
	int				Length;
	int				Allocated;
	char			baseBuffer [ STR_DEFAULT_ALLOC ];

public:
							crStr( void );
							crStr( const crStr& str);
							crStr( char* Text );
							crStr( float Float );
							crStr( bool Boolean );
							crStr( int Integer );
							crStr( unsigned int uInt );
							crStr( crVec2 vector2 );
							crStr( crVec3 vector3 );
							crStr( crVec4 vector4 );
							crStr( crQuaternion quat4 );
	virtual					~crStr( void );

	int						GetLength( void ) const;							// returns length of "Text"
	void					Append( char* aText );									
	void					Append( crStr String );								
	int						FindChar( char  Snippet ) const;					// returns 'Snippet''s first position in the string
//	void					Insert( unsigned int Position, char* Snippet );		// inserts 'Snippet' starting at "Position"
	crStr					Replace( char C, char R );							// replaces all 'C' with 'R'
	crStr					FromLeft( unsigned int len ) const;					// returns 'len' number of characters from left
	crStr					FromRight( unsigned int len ) const;							
//	crStr					FromMiddle( unsigned int len ) const;
//	void					ToLower( void );
//	void					ToUpper( void );
//	crStr					Lower( void ) const;
//	crStr					Upper( void ) const;

//	bool					operator==( crStr String );							// comparision of two strings
//	crStr					operator=( const crStr& String );					// "this" and "String" will be equivalent
	char*					operator()( void );									// returns "Text"
	char					operator[]( int Index );							// returns the character at position "Index"
/*	crStr					operator+( const crStr& String );	

	crStr&					operator+=( float Float );
	crStr&					operator+=( int Integer );
	crStr&					operator+=( unsigned int uInt );
	crStr&					operator+=( bool Boolean );
	
	crStr					GetFileExt( void ) const;							// searches for '.'-s from right
*/

protected:
	void					Reallocate( int newLength );						// reallocates memory for buffer
	void					Free( void );										// frees memory
	void					EnsureAllocated( int len );

	void					Init( void );

};

#endif /* __CRITEC_STRING_H_ */