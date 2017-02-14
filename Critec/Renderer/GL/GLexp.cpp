#include "glexp.h"

PFNGLMULTITEXCOORD1FPROC				glMultiTexCoord1f			= NULL;
PFNGLMULTITEXCOORD2FPROC				glMultiTexCoord2f			= NULL;
PFNGLMULTITEXCOORD3FPROC				glMultiTexCoord3f			= NULL;
PFNGLMULTITEXCOORD4FPROC				glMultiTexCoord4f			= NULL;
PFNGLACTIVETEXTUREPROC				    glActiveTexture				= NULL;
PFNGLCLIENTACTIVETEXTUREPROC			glClientActiveTexture		= NULL;
PFNGLUSEPROGRAMPROC						glUseProgram				= NULL;
PFNGLCREATEPROGRAMPROC					glCreateProgram				= NULL;
PFNGLDELETEPROGRAMPROC					glDeleteProgram				= NULL;
PFNGLCREATESHADERPROC					glCreateShader				= NULL;
PFNGLDELETESHADERPROC					glDeleteShader				= NULL;
PFNGLSHADERSOURCEPROC					glShaderSource				= NULL;
PFNGLATTACHSHADERPROC					glAttachShader				= NULL;
PFNGLLINKPROGRAMPROC				    glLinkProgram				= NULL;
PFNGLCOMPILESHADERPROC					glCompileShader				= NULL;
PFNGLGENQUERIESPROC						glGenQueries				= NULL;
PFNGLDELETEQUERIESPROC					glDeleteQueries				= NULL;
PFNGLISQUERYPROC						glIsQuery					= NULL;
PFNGLBEGINQUERYPROC						glBeginQuery				= NULL;
PFNGLENDQUERYPROC						glEndQuery					= NULL;
PFNGLPOINTPARAMETERFPROC				glPointParameterf			= NULL;
PFNGLPOINTPARAMETERFVPROC				glPointParameterfv			= NULL;
PFNWGLSWAPINTERVALEXTPROC				wglSwapIntervalEXT			= NULL;
PFNGLGETUNIFORMLOCATIONPROC				glGetUniformLocation		= NULL;
PFNGLUNIFORM1FPROC						glUniform1f					= NULL;
PFNGLUNIFORM2FPROC						glUniform2f					= NULL;
PFNGLUNIFORM3FPROC						glUniform3f					= NULL;
PFNGLUNIFORM4FPROC						glUniform4f					= NULL;
PFNGLUNIFORM1IPROC						glUniform1i					= NULL;
PFNGLUNIFORM2IPROC						glUniform2i					= NULL;
PFNGLUNIFORM3IPROC						glUniform3i					= NULL;
PFNGLUNIFORM4IPROC						glUniform4i					= NULL;
PFNGLUNIFORM2FVPROC						glUniform2fv				= NULL;
PFNGLUNIFORM3FVPROC						glUniform3fv				= NULL;
PFNGLUNIFORM4FVPROC						glUniform4fv				= NULL;
PFNGLUNIFORMMATRIX2FVPROC				glUniformMatrix2fv			= NULL;
PFNGLUNIFORMMATRIX3FVPROC				glUniformMatrix3fv			= NULL;
PFNGLUNIFORMMATRIX4FVPROC				glUniformMatrix4fv			= NULL;
PFNGLBLENDFUNCSEPARATEPROC				glBlendFuncSeparate			= NULL;
PFNGLFOGCOORDFPROC						glFogCoordf					= NULL;
PFNGLFOGCOORDFVPROC						glFogCoordfv				= NULL;
PFNGLFOGCOORDDPROC						glFogCoordd					= NULL;
PFNGLFOGCOORDDVPROC						glFogCoordddv				= NULL;
PFNGLGENBUFFERSPROC						glGenBuffers				= NULL;
PFNGLBINDBUFFERPROC						glBindBuffer				= NULL;
PFNGLBUFFERDATAPROC						glBufferData				= NULL;
PFNGLBUFFERSUBDATAPROC					glBufferSubData				= NULL;
PFNGLDELETEBUFFERSPROC					glDeleteBuffers				= NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC					glRenderbufferStorageEXT					= NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC			glGetRenderbufferParameterivEXT				= NULL;
PFNGLISFRAMEBUFFEREXTPROC						glIsFrameBufferEXT							= NULL;
PFNGLBINDFRAMEBUFFEREXTPROC						glBindFramebufferEXT 						= NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC					glDeleteFramebuffersEXT						= NULL;
PFNGLGENFRAMEBUFFERSEXTPROC						glGenFramebuffersEXT						= NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT					= NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT 					= NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT					= NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT					= NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT 				= NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC	glGetFramebufferAttachmentParameterivEXT 	= NULL;
PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT 						= NULL;
PFNGLGENRENDERBUFFERSEXTPROC					glGenRenderbuffersEXT						= NULL;
PFNGLDELETERENDERBUFFERSEXTPROC					glDeleteRenderbuffersEXT					= NULL;
PFNGLBINDRENDERBUFFEREXTPROC					glBindRenderbufferEXT						= NULL;
PFNGLISRENDERBUFFEREXTPROC						glIsRenderbufferEXT							= NULL;
PFNGLCLAMPCOLORARBPROC							glClampColorARB								= NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC					wglChoosePixelFormatARB						= NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC					glCompressedTexImage2D						= NULL;
PFNGLVERTEXATTRIB3FPROC							glVertexAttrib3fARB							= NULL;
PFNGLGETATTRIBLOCATIONARBPROC					glGetAttribLocationARB						= NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC				    glVertexAttribPointerARB					= NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC				glEnableVertexAttribArrayARB				= NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC			glDisableVertexAttribArrayARB				= NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC		glRenderbufferStorageMultisampleEXT			= NULL;
PFNGLBLENDEQUATIONEXTPROC						glBlendEquationEXT							= NULL;
PFNGLDRAWBUFFERSPROC							glDrawBuffers								= NULL;
//PFNGLDRAWBUFFERPROC								glDrawBuffer								= NULL;
PFNGLBLITFRAMEBUFFEREXTPROC						glBlitFramebufferEXT						= NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC				wglGetExtensionsStringARB;


char* GetOpenGLVersion( void ) {
	return (char*)glGetString(GL_VERSION);
}

void LoadOpenGLCore( void ) {
	glActiveTexture				= (PFNGLACTIVETEXTUREPROC)   wglGetProcAddress("glActiveTexture");
    glMultiTexCoord2f			= (PFNGLMULTITEXCOORD2FPROC) wglGetProcAddress("glMultiTexCoord2f");
	glMultiTexCoord3f			= (PFNGLMULTITEXCOORD3FPROC) wglGetProcAddress("glMultiTexCoord3f");
	glUseProgram				= (PFNGLUSEPROGRAMPROC)		 wglGetProcAddress("glUseProgram");
	glCreateProgram				= (PFNGLCREATEPROGRAMPROC)   wglGetProcAddress("glCreateProgram");
	glDeleteProgram				= (PFNGLDELETEPROGRAMPROC)   wglGetProcAddress("glDeleteProgram");
	glCreateShader				= (PFNGLCREATESHADERPROC)	 wglGetProcAddress("glCreateShader");
	glDeleteShader				= (PFNGLDELETESHADERPROC)	 wglGetProcAddress("glDeleteShader");
	glShaderSource				= (PFNGLSHADERSOURCEPROC)    wglGetProcAddress("glShaderSource");
	glAttachShader				= (PFNGLATTACHSHADERPROC)	 wglGetProcAddress("glAttachShader");
	glLinkProgram				= (PFNGLLINKPROGRAMPROC)	 wglGetProcAddress("glLinkProgram");
	glCompileShader				= (PFNGLCOMPILESHADERPROC)	 wglGetProcAddress("glCompileShader");
	glGenQueries				= (PFNGLGENQUERIESPROC)      wglGetProcAddress("glGenQueries");
	glDeleteQueries				= (PFNGLDELETEQUERIESPROC)   wglGetProcAddress("glDeleteQueries");
	glIsQuery					= (PFNGLISQUERYPROC)		 wglGetProcAddress("glIsQuery");
	glBeginQuery				= (PFNGLBEGINQUERYPROC)		 wglGetProcAddress("glBeginQuery");
	glEndQuery					= (PFNGLENDQUERYPROC)		 wglGetProcAddress("glEndQuery");
	glPointParameterf			= (PFNGLPOINTPARAMETERFPROC) wglGetProcAddress("glPointParameterf");
	glPointParameterfv			= (PFNGLPOINTPARAMETERFVPROC)wglGetProcAddress("glPointParameterfv");
	glGetUniformLocation		= (PFNGLGETUNIFORMLOCATIONPROC)	 wglGetProcAddress("glGetUniformLocation");
	glUniform1f					= (PFNGLUNIFORM1FPROC)	     wglGetProcAddress("glUniform1f");
	glUniform2f					= (PFNGLUNIFORM2FPROC)	     wglGetProcAddress("glUniform2f");
	glUniform3f					= (PFNGLUNIFORM3FPROC)	     wglGetProcAddress("glUniform3f");
	glUniform4f					= (PFNGLUNIFORM4FPROC)	     wglGetProcAddress("glUniform4f");
	glUniform1i					= (PFNGLUNIFORM1IPROC)	     wglGetProcAddress("glUniform1i");
	glUniform2i					= (PFNGLUNIFORM2IPROC)	     wglGetProcAddress("glUniform2i");
	glUniform3i					= (PFNGLUNIFORM3IPROC)	     wglGetProcAddress("glUniform3i");
	glUniform4i					= (PFNGLUNIFORM4IPROC)	     wglGetProcAddress("glUniform4i");
	glUniform2fv				= (PFNGLUNIFORM2FVPROC)		 wglGetProcAddress("glUniform2fv");
	glUniform3fv				= (PFNGLUNIFORM3FVPROC)		 wglGetProcAddress("glUniform3fv");
	glUniform4fv				= (PFNGLUNIFORM4FVPROC)		 wglGetProcAddress("glUniform4fv");
	glUniformMatrix2fv			= (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv			= (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv			= (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glBlendFuncSeparate			= (PFNGLBLENDFUNCSEPARATEPROC)wglGetProcAddress("glBlendFuncSeparate");
	glFogCoordf					= (PFNGLFOGCOORDFPROC)		 wglGetProcAddress("glFogCoordf");
	glFogCoordfv				= (PFNGLFOGCOORDFVPROC)		 wglGetProcAddress("glFogCoordfv");
	glFogCoordd					= (PFNGLFOGCOORDDPROC)		 wglGetProcAddress("glFogCoordd");
	glFogCoordddv				= (PFNGLFOGCOORDDVPROC)		 wglGetProcAddress("glFogCoorddv");
	glClientActiveTexture		= (PFNGLCLIENTACTIVETEXTUREPROC) wglGetProcAddress("glClientActiveTexture");
	glGenBuffers				= (PFNGLGENBUFFERSPROC)	 	 wglGetProcAddress("glGenBuffersARB");
	glBindBuffer				= (PFNGLBINDBUFFERPROC)	 	 wglGetProcAddress("glBindBuffer");
	glBufferData				= (PFNGLBUFFERDATAPROC)		 wglGetProcAddress("glBufferData");
	glBufferSubData				= (PFNGLBUFFERSUBDATAPROC)	 wglGetProcAddress("glBufferSubData");
	glDeleteBuffers				= (PFNGLDELETEBUFFERSPROC)	 wglGetProcAddress("glDeleteBuffers");
	glCompressedTexImage2D		= (PFNGLCOMPRESSEDTEXIMAGE2DPROC)	wglGetProcAddress("glCompressedTexImage2D");
	glDrawBuffers				= (PFNGLDRAWBUFFERSPROC)			wglGetProcAddress("glDrawBuffers");
}

bool IsGLExtensionSupported( char* extname ) {
	char* extList = (char*)glGetString( GL_EXTENSIONS );

	if(strstr(extList, extname)) return true;
	else return false;
}

bool IsWGLExtensionSupported( char* extname ) {
	LoadEXT_WGL_ARB_extensions_string();
	char* extList = (char*)wglGetExtensionsStringARB( wglGetCurrentDC() );

	if(strstr(extList, extname)) return true;
	else return false;
}

bool LoadEXT_WGL_ARB_extensions_string( void ) {
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
	return true;
}

bool LoadEXT_WGL_EXT_swap_control( void ) {
	if(!IsWGLExtensionSupported("WGL_EXT_swap_control")) return false;
	wglSwapIntervalEXT			= (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	return true;
}

bool LoadEXT_WGL_ARB_pixel_format( void ) {
	if(!IsWGLExtensionSupported("WGL_ARB_pixel_format")) return false;
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
	return true;
}

bool LoadEXT_GL_EXT_blend_minmax( void ) {
	if(!IsGLExtensionSupported("GL_EXT_blend_minmax")) return false;
	glBlendEquationEXT	= (PFNGLBLENDEQUATIONEXTPROC)wglGetProcAddress("glBlendEquationEXT");
	return true;
}

bool LoadEXT_GL_EXT_framebuffer_multisample( void ) {
	if(!IsGLExtensionSupported("GL_EXT_framebuffer_blit")) return false;
	glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) wglGetProcAddress("glRenderbufferStorageMultisampleEXT");
	return true;
}

bool LoadEXT_GL_EXT_framebuffer_object( void ) {
	if(!IsGLExtensionSupported("GL_EXT_framebuffer_object")) return false;
	glIsRenderbufferEXT			= (PFNGLISRENDERBUFFEREXTPROC)		wglGetProcAddress("glIsRenderbufferEXT");
	glBindRenderbufferEXT		= (PFNGLBINDRENDERBUFFEREXTPROC)	wglGetProcAddress("glBindRenderbufferEXT");
	glDeleteRenderbuffersEXT		= (PFNGLDELETERENDERBUFFERSEXTPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
	glGenRenderbuffersEXT			= (PFNGLGENRENDERBUFFERSEXTPROC)	wglGetProcAddress("glGenRenderbuffersEXT");
	glRenderbufferStorageEXT		= (PFNGLRENDERBUFFERSTORAGEEXTPROC)		wglGetProcAddress("glRenderbufferStorageEXT");
	glGetRenderbufferParameterivEXT	= (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)	wglGetProcAddress("glGetRenderbufferParameterivEXT");
	glBindFramebufferEXT			= (PFNGLBINDFRAMEBUFFEREXTPROC)			wglGetProcAddress("glBindFramebufferEXT");
	glIsFrameBufferEXT			= (PFNGLISFRAMEBUFFEREXTPROC)					wglGetProcAddress("glIsFrameBufferEXT");
	glDeleteFramebuffersEXT		= (PFNGLDELETEFRAMEBUFFERSEXTPROC)				wglGetProcAddress("glDeleteFramebuffersEXT");
	glGenFramebuffersEXT			= (PFNGLGENFRAMEBUFFERSEXTPROC)			wglGetProcAddress("glGenFramebuffersEXT");
	glCheckFramebufferStatusEXT	= (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)			wglGetProcAddress("glCheckFramebufferStatusEXT");
	glFramebufferTexture1DEXT			= (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)	wglGetProcAddress("glFramebufferTexture1DEXT");
	glFramebufferTexture2DEXT			= (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)	wglGetProcAddress("glFramebufferTexture2DEXT");
	glFramebufferTexture3DEXT			= (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)	wglGetProcAddress("glFramebufferTexture3DEXT");
	glFramebufferRenderbufferEXT	= (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)	wglGetProcAddress("glFramebufferRenderbufferEXT");
	glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
	return true;
}

bool LoadEXT_GL_EXT_framebuffer_blit( void ) {
	if(!IsGLExtensionSupported("GL_EXT_framebuffer_blit")) return false;
	glBlitFramebufferEXT		= (PFNGLBLITFRAMEBUFFEREXTPROC)				wglGetProcAddress("glBlitFramebufferEXT");
	return true;
}

bool LoadEXT_GL_ARB_vertex_shader( void ) {
	if(!IsGLExtensionSupported("GL_ARB_vertex_shader")) return false;
	glVertexAttrib3fARB				=(PFNGLVERTEXATTRIB3FPROC)					wglGetProcAddress("glVertexAttrib3fARB");
	glGetAttribLocationARB			=(PFNGLGETATTRIBLOCATIONARBPROC)			wglGetProcAddress("glGetAttribLocationARB");
	glVertexAttribPointerARB		=(PFNGLVERTEXATTRIBPOINTERARBPROC)			wglGetProcAddress("glVertexAttribPointerARB");
	glEnableVertexAttribArrayARB	=(PFNGLENABLEVERTEXATTRIBARRAYARBPROC)		wglGetProcAddress("glEnableVertexAttribArrayARB");
	glDisableVertexAttribArrayARB	=(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)		wglGetProcAddress("glDisableVertexAttribArrayARB");
	return true;
}
