
/*
=========================================================================
 
 Bugs:
	FromLeft() & FromRight() does not work.

=========================================================================
*/

#include "String.h"

crStr::crStr( void ) {
	Init();
}

crStr::crStr( char* aText ) {
	Init();
	unsigned int len = strlen( aText );
	EnsureAllocated( len + 1 );
	strcpy_s(Text, len + 1, aText);
	Length = len;
}

crStr::crStr( const crStr& str) {
	Init();
	EnsureAllocated( str.Length + 1);
	strcpy_s( Text, str.Length + 1, str.Text );
	Length    = str.Length;
}

crStr::crStr( float Float ) {
	Init();
	char vs[9];
	sprintf_s(vs, 9, "%5.3f", Float);
	EnsureAllocated( 10 );
	strcpy_s(Text, 10, vs);
	Length = 9;
}

crStr::crStr( bool Boolean ) {
	Init();
	char* _state = (Boolean)? "true" : "false";
	EnsureAllocated( strlen(_state) + 1 );
	strcpy_s(Text, strlen(_state)+1, _state);
	Length = strlen(_state);
}

crStr::crStr( int Integer ) {
	Init();
	char vs[6];
	sprintf_s(vs, 6, "%d", Integer);
	EnsureAllocated( strlen(vs) + 1 );
	strcpy_s( Text, strlen(vs) + 1, vs );
	Length = strlen(vs);
}

crStr::crStr( unsigned int uInt ) {
	Init();
	char vs[6];
	sprintf_s(vs, 6, "%d", uInt);
	EnsureAllocated( strlen(vs) + 1 );
	strcpy_s( Text, strlen(vs) + 1, vs );
	Length = strlen(vs);
}

crStr::crStr( crVec2 vector2 ) {
	Init();
	char vs[64];
	sprintf_s(vs, 64, "%5.3f/%5.3f", vector2.x, vector2.y);

	unsigned int l = strlen(vs);
	EnsureAllocated( l + 1 );
	strcpy_s( Text, l+1, vs );
	Length = l;
}

crStr::crStr( crVec3 vector3 ) {
	Init();
	
	char vs[64];
	sprintf_s(vs, 64, "%5.3f/%5.3f/%5.3f", vector3.x, vector3.y, vector3.z ); 

	unsigned int l = strlen(vs);
	EnsureAllocated( l + 1 );
	strcpy_s( Text, l+1, vs );
	Length = l;
}

crStr::crStr( crVec4 vector4 ) {
	Init();
	
	char vs[92];
	sprintf_s(vs, 92, "%5.3f/%5.3f/%5.3f/%5.3f", vector4.x, vector4.y, vector4.z, vector4.w );

	unsigned int l = strlen(vs);
	EnsureAllocated( l + 1 );
	strcpy_s( Text, l+1, vs );
	Length = l;
}

crStr::crStr( crQuaternion quat4 ) {
	Init();
	
	char vs[42];
	sprintf_s(vs, 42, "%5.3f/%5.3f/%5.3f/%5.3f", quat4.x, quat4.y, quat4.z, quat4.w );
	
	unsigned int l = strlen(vs);
	EnsureAllocated( l + 1 );
	strcpy_s( Text, l+1, vs );

	Length = l;
}

crStr::~crStr( void ) {
	Free ();
}

char* crStr::operator ()( void ) {
	return Text;
}

char crStr::operator[] ( int Index ) {
	return (Index>0 && Index<Length)? Text[Index] : '\0';
}

void crStr::Append( char* aText ) {
	if ( aText ) {
		int newLen = Length + strlen(aText);
		EnsureAllocated( newLen + 1 );
		for(unsigned int i=0; i<strlen(aText); i++)
			Text[Length + i] = aText[ i ];
		Text[newLen] = '\0';
		Length = newLen;
	}
}

void crStr::Append( crStr String ) {
	int newLength = Length + String.Length;
	EnsureAllocated( newLength + 1 );
	for (int i=0; i<String.Length; i++)
		Text[Length + i ] = String.Text[i];
	Text[newLength] = '\0';
	Length = newLength;
}

int crStr::FindChar( char Snippet ) const {
	for (int i=0; i<Length; i++)
		if (Text[i] == Snippet) return i;
	return 0;
}

crStr crStr::Replace( char C, char R ) {
	for (int i=0; i<Length; i++)
		if (Text[i] == C) Text[i] = R;

	crStr return_value(Text);
	return return_value;
}

int crStr::GetLength( void ) const {
	return Length;
}

crStr crStr::FromLeft( unsigned int len ) const {
	crStr ret;

	if (Length == 0) return ret;
	if (len>(unsigned int)Length) len = (unsigned int)Length;

	char* pChar = new char[len];
	for (unsigned int i = 0; i<len; i++)
		pChar[i] = Text[i];

	ret.Append(pChar);

	//MSGBOX(ret.Text);

	return ret;
}

crStr crStr::FromRight( unsigned int len ) const {
	crStr ret;
	if (Text == baseBuffer) return ret;
	if (len>(unsigned int)Length) len = (unsigned int)Length;
	for (unsigned int i = Length; i>Length-len; i++)
		ret.Append(&Text[i]);

	return ret;
}


/*
=============================

  Memory management

=============================
*/
void crStr::Init( void ) {
	Allocated = STR_DEFAULT_ALLOC;
	Text = baseBuffer;
	Length = 0;
	//instead memset:
	for ( int i=0; i<Allocated; i++)
		Text[i] = '\0';
}

void crStr::Reallocate( int newLength ) {
	char* newBuffer = new char[newLength];
	
	Text[Length] = '\0';
	//strcpy_s(newBuffer, Allocated, Text);
	for (int i=0; i<Allocated; i++) 
		newBuffer[i] = Text[i];
	
	delete [] Text;

	Text = newBuffer;

	Allocated = newLength;
}

void crStr::Free( void ) {
	if( Text && Text != baseBuffer ) {
		delete [] Text;
		Text = baseBuffer;
		Allocated = STR_DEFAULT_ALLOC;
		Length = 0;
	}
}

void crStr::EnsureAllocated( int len ) {
	if (len > Allocated) {
		Reallocate( len );
	}
}