#include "FileManager.h"

/*
=================================
 crRestoreFile
=================================
*/
crRestoreFile::crRestoreFile( void ) {
	FileDescriptor	= NULL;
	Size			= NULL;
}

crRestoreFile::~crRestoreFile( void ) {
	Size = 0;
	FileDescriptor = NULL;
}

bool crRestoreFile::Open( const char* FileName ) {
	this->FileName = (char*)FileName;
	fopen_s(&FileDescriptor, FileName, "rb+");

	if (!FileDescriptor) {
		MSGBOX("%s does not exist", GetName());
		return false;
	}
	Size = GetSize();
	Opened = true;
	return true;
}

void crRestoreFile::Close( void ) { 
	fclose(FileDescriptor);
	Opened = false;
}

long crRestoreFile::Tell( void ) {
	return ftell(FileDescriptor);
}

long crRestoreFile::GetSize( void ) {
	if(!Opened) return 0;
	long curr = ftell(FileDescriptor);
	fseek(FileDescriptor, 0, SEEK_END);
	long end = ftell(FileDescriptor);
	fseek(FileDescriptor, curr, SEEK_SET);
	return end;
}


FILE* crRestoreFile::GetDescriptor( void ) { 
	return FileDescriptor;
}

char* crRestoreFile::GetName( void ) { 
	return FileName;
}

bool crRestoreFile::Seek( long Offset, int Origin ) { 
	if(!Opened) return false;
	fseek(FileDescriptor, Offset, Origin);
	return true;
}

bool crRestoreFile::Read( void* Buffer, unsigned int Size ) { 
	if(!Opened) return false;
	fread(Buffer,  Size, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadByte( unsigned char* Buffer ) {
	if(!Opened) return false;
	fread(Buffer,  1, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadChar( char* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(char), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadLong( long* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(long), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadShort( short* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(short), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadUnsignedShort( unsigned short* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(unsigned short), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadFloat( float* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadInt( int* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(int), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadBool( bool* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(bool), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadUnsignedInt( unsigned int* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(unsigned int), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadDouble( double* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(double), 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadcrVec2( crVec2* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float)*2, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadcrVec3( crVec3* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float)*3, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadcrVec4( crVec4* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float)*4, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadcrMat3( crMat3* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float)*9, 1, FileDescriptor);
	return true;
}

bool crRestoreFile::ReadcrMat4( crMat4* Buffer ) { 
	if(!Opened) return false;
	fread(Buffer,  sizeof(float)*16, 1, FileDescriptor);
	return true;
}



/*
===========================
 crSaveFile
===========================
*/
crSaveFile::crSaveFile( void ) {
	FileDescriptor	= NULL;
	Size			= NULL;
}

crSaveFile::~crSaveFile( void ) {
	Size = 0;
	FileDescriptor = NULL;
}

bool crSaveFile::Open( const char* FileName ) {
	this->FileName = (char*)FileName;
	fopen_s(&FileDescriptor, FileName, "rb+");

	if (!FileDescriptor) {
		MSGBOX("%s does not exist", GetName());
		return false;
	}
	Size = GetSize();
	Opened = true;
	return true;
}

void crSaveFile::Close( void ) { 
	fclose(FileDescriptor);
	Opened = false;
}

long crSaveFile::Tell( void ) {
	return ftell(FileDescriptor);
}

long crSaveFile::GetSize( void ) {
	if(!Opened) return 0;
	long curr = ftell(FileDescriptor);
	fseek(FileDescriptor, 0, SEEK_END);
	long end = ftell(FileDescriptor);
	fseek(FileDescriptor, curr, SEEK_SET);
	return end;
}


FILE* crSaveFile::GetDescriptor( void ) { 
	return FileDescriptor;
}

char* crSaveFile::GetName( void ) { 
	return FileName;
}

bool crSaveFile::Seek( long Offset, int Origin ) { 
	if(!Opened) return false;
	fseek(FileDescriptor, Offset, Origin);
	return true;
}

bool crSaveFile::Write( void* Buffer, unsigned int Size ) { 
	if(!Opened) return false;
	fwrite(Buffer,  Size, 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteByte( unsigned char* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(unsigned char), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteChar( char* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(char), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteLong( long* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(long), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteShort( short* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(short), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteUnsignedShort( unsigned short* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(unsigned short), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteFloat( float* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteUnsignedInt( unsigned int* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(unsigned int), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteInt( int* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(int), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteBool( bool* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(bool), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WriteDouble( double* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(double), 1, FileDescriptor);
	return true;
}

bool crSaveFile::WritecrVec2( crVec2* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float)*2, 1, FileDescriptor);
	return true;
}

bool crSaveFile::WritecrVec3( crVec3* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float)*3, 1, FileDescriptor);
	return true;
}

bool crSaveFile::WritecrVec4( crVec4* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float)*4, 1, FileDescriptor);
	return true;
}

bool crSaveFile::WritecrMat3( crMat3* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float)*9, 1, FileDescriptor);
	return true;
}

bool crSaveFile::WritecrMat4( crMat4* Buffer ) { 
	if(!Opened) return false;
	fwrite(Buffer,  sizeof(float)*16, 1, FileDescriptor);
	return true;
}
