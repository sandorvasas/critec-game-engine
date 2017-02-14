#include "ShaderManager.h"
#include "../Framework/Array.h"
#include "gl/glexp.h"
#include "../Managers/FileManager.h"

crGLSLShader::crGLSLShader( void ) {
	FragmentShader = 0;
	VertexShader = 0;
	GeometryShader = 0;
}
crGLSLShader::~crGLSLShader( void ) {
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
	glDeleteShader(GeometryShader);
	glDeleteProgram(program);
}


bool crGLSLShader::LoadFromFile( char* filename ) {
	crRestoreFile File;
	if(!File.Open(filename)) return false;

	char *source = new char[File.GetSize()+1];

	for (unsigned int i=0; i<File.GetSize()/sizeof(char); i++) 
		File.ReadChar(&source[i]);

	source[File.GetSize()] = '\0';

	LoadFromSource(source);

	File.Close();

	delete [] source;
	return true;
}

bool crGLSLShader::LoadFromSource( char* source ) {

	if (source == NULL) return false;

	crArray<char> sfrag, svert, sgeom;
	int i=0;
	int len = (int)strlen((const char*) source);
		
	char c;
	while (i<len) {
		c = source[i];

		switch (c) {
			case 'ß' : if (i<len-1) {
							if (source[i+1]=='F') {
								i+=2;
								while( i<len && source[i]!= 'ß' ) {
									sfrag.Append(source[i++]);
								}
								sfrag.Append('\0');
							}

							if (source[i+1]=='V') {
								i+=2;
								while( i<len && source[i]!= 'ß' ) {
									svert.Append(source[i++]);
								}
								svert.Append('\0');
						   }

						   if (source[i+1]=='G') {
								i+=2;
								while( i<len && source[i]!= 'ß' ) {
									sgeom.Append(source[i++]);
								}
								sgeom.Append('\0');
							}
					   }
			break;
			default: i++;
		}
	}

	if (sgeom.Count) {
		char* geom = new char[sgeom.Count];
		strcpy_s(geom, sgeom.Count, sgeom.Ptr());

		GeometryShader = glCreateShader(GL_GEOMETRY_SHADER_EXT);
		glShaderSource(GeometryShader, 1, (const char**)&geom, 0);
		glCompileShader(GeometryShader);

		delete [] geom;
	}

//	MessageBox(NULL, sfrag.Ptr(), "FRAG", MB_OK);
	if(sfrag.Count) {
		char* frag = new char[sfrag.Count];
		strcpy_s(frag, sfrag.Count, sfrag.Ptr());

		FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShader, 1, (const char**)&frag, 0);
		glCompileShader(FragmentShader);

		delete [] frag;
	}
	
//MessageBox(NULL, svert.Ptr(), "VERT", MB_OK);
	if (svert.Count) {
		char* vert = new char[svert.Count];
		strcpy_s(vert, svert.Count, svert.Ptr());

		VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShader, 1, (const char**)&vert, 0);
		glCompileShader(VertexShader);

		delete [] vert;
	}

	program = glCreateProgram();

	glAttachShader(program, FragmentShader);
	glAttachShader(program, VertexShader);
	glAttachShader(program, GeometryShader);

	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
	glDeleteShader(GeometryShader);

	glLinkProgram(program);

	return true;
}

void crGLSLShader::Activate( void ) {
	glUseProgram( program );
}

void crGLSLShader::Deactivate( void ) {
	glUseProgram( NULL );
}

unsigned int crGLSLShader::AttributeLoc( char attribute[] ) {
	return glGetAttribLocationARB(program, attribute);
}

unsigned int crGLSLShader::UniformLoc( char uniform[] ) {
	return glGetUniformLocation(program, uniform);
}

void crGLSLShader::Uniform1f( char* uniform, float f ) {
	glUniform1f(UniformLoc(uniform), f );
}

void crGLSLShader::Uniform2f( char* uniform, float x, float y ) {
	glUniform2f(UniformLoc(uniform), x, y );
}

void crGLSLShader::Uniform3f( char* uniform, float x, float y, float z ) {
	glUniform3f(UniformLoc(uniform), x, y, z );
}

void crGLSLShader::Uniform4f( char* uniform, float x, float y, float z, float w ) {
	glUniform4f(UniformLoc(uniform), x, y, z, w );
}

void crGLSLShader::Uniform1i( char* uniform, int f ) {
	glUniform1i(UniformLoc(uniform), f );
}

void crGLSLShader::Uniform2i( char* uniform, int x, int y ) {
	glUniform2i(UniformLoc(uniform), x, y );
}

void crGLSLShader::Uniform3i( char* uniform, int x, int y, int z ) {
	glUniform3i(UniformLoc(uniform), x, y, z );
}

void crGLSLShader::Uniform4i( char* uniform, int x, int y, int z, int w ) {
	glUniform4i(UniformLoc(uniform), x, y, z, w );
}

void crGLSLShader::UniformVector2( char* uniform, int count, float* v ) {
	glUniform2fv(UniformLoc(uniform), count, v);
}

void crGLSLShader::UniformVector3( char* uniform, int count, float* v ) {
	glUniform3fv(UniformLoc(uniform), count, v);
}

void crGLSLShader::UniformVector4( char* uniform, int count, float* v ) {
	glUniform4fv(UniformLoc(uniform), count, v);
}

void crGLSLShader::UniformMatrix2( char* uniform, bool transpose, crMat2 M ) {
	glUniformMatrix2fv(UniformLoc(uniform), 1, transpose, M.ToFloatPtr());
}

void crGLSLShader::UniformMatrix3( char* uniform, bool transpose, crMat3 M ) {
	glUniformMatrix3fv(UniformLoc(uniform), 1, transpose, M.ToFloatPtr());
}

void crGLSLShader::UniformMatrix4( char* uniform, bool transpose, crMat4 M ) {
	glUniformMatrix4fv(UniformLoc(uniform), 1, transpose, M.ToFloatPtr());
}