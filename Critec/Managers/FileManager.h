// FileManager.h
// Copyright (C) 2007 by Sandor Vasas
//
#ifndef __CRITEC_FILEMANAGER_H_
#define __CRITEC_FILEMANAGER_H_

#include <stdio.h>
#include "../Math/Math3D.h"
#include "../Framework/System.h"
#pragma hdrstop

class crRestoreFile {
protected:
	bool					Opened;

public:
	char*					FileName;
	FILE*					FileDescriptor;
	long 					Size;

public:
							crRestoreFile( void );
							~crRestoreFile( void );

	virtual bool			Open( const char* FileName );
	void					Close( void );
	long					Tell( void );
	long					GetSize( void );
	FILE*					GetDescriptor( void );
	char*					GetName( void );

	bool					Seek( long Offset, int Origin );
	bool					Read( void* Buffer, unsigned int Size );

	bool					ReadByte( unsigned char* Buffer );
	bool					ReadChar( char* Buffer );
	bool					ReadLong( long* Buffer );
	bool					ReadShort( short* Buffer );
	bool					ReadUnsignedShort( unsigned short* Buffer );
	bool					ReadFloat( float* Buffer );
	bool					ReadInt( int* Buffer );
	bool					ReadBool( bool* Buffer );
	bool					ReadUnsignedInt( unsigned int* Buffer );
	bool					ReadDouble( double* Buffer );
	bool					ReadcrVec2( crVec2* Buffer );
	bool					ReadcrVec3( crVec3* Buffer );
	bool					ReadcrVec4( crVec4* Buffer );
	bool					ReadcrMat3( crMat3* Buffer );		
	bool					ReadcrMat4( crMat4* Buffer );
};

class crSaveFile {
protected:
	bool					Opened;

public:
	char*					FileName;
	FILE*					FileDescriptor;
	long 					Size;

public:
							crSaveFile( void );
							~crSaveFile( void );

	virtual bool			Open( const char* FileName );
	void					Close( void );
	long					Tell( void );
	long					GetSize( void );
	FILE*					GetDescriptor( void );
	char*					GetName( void );
	bool					Seek( long Offset, int Origin );
	bool					Write( void* Buffer, unsigned int Size );
	bool					WriteByte( unsigned char* Buffer );
	bool					WriteChar( char* Buffer );
	bool					WriteLong( long* Buffer );
	bool					WriteShort( short* Buffer );
	bool					WriteUnsignedShort( unsigned short* Buffer );
	bool					WriteFloat( float* Buffer );
	bool					WriteUnsignedInt( unsigned int* Buffer );
	bool					WriteInt( int* Buffer );
	bool					WriteBool( bool* Buffer );
	bool					WriteDouble( double* Buffer );
	bool					WritecrVec2( crVec2* Buffer );
	bool					WritecrVec3( crVec3* Buffer );
	bool					WritecrVec4( crVec4* Buffer );
	bool					WritecrMat3( crMat3* Buffer );		
	bool					WritecrMat4( crMat4* Buffer );
};

#endif