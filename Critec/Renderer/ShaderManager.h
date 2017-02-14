// Copyright (C) 2007 by Sandor Vasas

#ifndef __CRITEC_SHADERMANAGER_H__
#define __CRITEC_SHADERMANAGER_H__

#include "../Math/Math3d.h"
#pragma hdrstop


class crGLSLShader {
private:
	unsigned int	program;

public:
	unsigned int	FragmentShader;
	unsigned int	VertexShader;
	unsigned int	GeometryShader;
	
public:
					crGLSLShader( void );
	virtual			~crGLSLShader( void );

	void			Activate( void );
	void			Deactivate( void );
	unsigned int	UniformLoc( char uniform[] );		
	unsigned int	AttributeLoc( char attribute[] );

	bool			LoadFromFile( char* filename );
	bool			LoadFromSource( char* source );

	void			Uniform1f( char* uniform, float f );
	void			Uniform2f( char* uniform, float x, float y );
	void			Uniform3f( char* uniform, float x, float y, float z );
	void			Uniform4f( char* uniform, float x, float y, float z, float w );

	void			Uniform1i( char* uniform, int f );
	void			Uniform2i( char* uniform, int x, int y );
	void			Uniform3i( char* uniform, int x, int y, int z );
	void			Uniform4i( char* uniform, int x, int y, int z, int w );

	void			UniformVector2( char* uniform, int count, float* v );
	void			UniformVector3( char* uniform, int count, float* v );
	void			UniformVector4( char* uniform, int count, float* v );

	void			UniformMatrix2( char* uniform, bool transpose, crMat2 M );
	void			UniformMatrix3( char* uniform, bool transpose, crMat3 M );
	void			UniformMatrix4( char* uniform, bool transpose, crMat4 M );
};



#endif