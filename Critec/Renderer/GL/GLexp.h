// Copyright (C) 2006-2007 by sonka

#ifndef __CRITEC_GLEXP_H__
#define __CRITEC_GLEXP_H__

#include <windows.h>
#include "GL.h"
#include "GLext.h"
#include "WGLext.h"

#pragma comment (lib, "Opengl32.lib")

char*	GetOpenGLVersion( void );
void	LoadOpenGLCore( void );

bool	IsGLExtensionSupported( char* extname );
bool	IsWGLExtensionSupported( char* extname );

bool	LoadEXT_WGL_ARB_extensions_string( void );
bool	LoadEXT_WGL_EXT_swap_control( void );
bool	LoadEXT_WGL_ARB_pixel_format( void );

bool	LoadEXT_GL_EXT_framebuffer_object( void );
bool	LoadEXT_GL_EXT_framebuffer_blit( void );
bool	LoadEXT_GL_EXT_blend_minmax( void );
bool	LoadEXT_GL_EXT_framebuffer_multisample( void );
bool	LoadEXT_GL_ARB_vertex_shader( void );


/* CORE */
extern PFNGLMULTITEXCOORD1FPROC									glMultiTexCoord1f			;
extern PFNGLMULTITEXCOORD2FPROC									glMultiTexCoord2f			;
extern PFNGLMULTITEXCOORD3FPROC									glMultiTexCoord3f			;
extern PFNGLMULTITEXCOORD4FPROC									glMultiTexCoord4f			;
extern PFNGLACTIVETEXTUREPROC								    glActiveTexture				;
extern PFNGLCLIENTACTIVETEXTUREPROC								glClientActiveTexture		;
extern PFNGLUSEPROGRAMPROC										glUseProgram				;
extern PFNGLCREATEPROGRAMPROC									glCreateProgram				;
extern PFNGLDELETEPROGRAMPROC									glDeleteProgram				;
extern PFNGLCREATESHADERPROC									glCreateShader				;
extern PFNGLDELETESHADERPROC									glDeleteShader				;
extern PFNGLSHADERSOURCEPROC									glShaderSource				;
extern PFNGLATTACHSHADERPROC									glAttachShader				;
extern PFNGLLINKPROGRAMPROC										glLinkProgram				;
extern PFNGLCOMPILESHADERPROC									glCompileShader				;
extern PFNGLGENQUERIESPROC										glGenQueries				;
extern PFNGLDELETEQUERIESPROC									glDeleteQueries				;
extern PFNGLISQUERYPROC											glIsQuery					;
extern PFNGLBEGINQUERYPROC										glBeginQuery				;
extern PFNGLENDQUERYPROC										glEndQuery					;
extern PFNGLPOINTPARAMETERFPROC									glPointParameterf			;
extern PFNGLPOINTPARAMETERFVPROC								glPointParameterfv			;
extern PFNGLGETUNIFORMLOCATIONPROC								glGetUniformLocation		;
extern PFNGLUNIFORM1FPROC										glUniform1f;
extern PFNGLUNIFORM2FPROC										glUniform2f;
extern PFNGLUNIFORM3FPROC										glUniform3f;
extern PFNGLUNIFORM4FPROC										glUniform4f;
extern PFNGLUNIFORM1IPROC										glUniform1i;
extern PFNGLUNIFORM2IPROC										glUniform2i;
extern PFNGLUNIFORM3IPROC										glUniform3i;
extern PFNGLUNIFORM4IPROC										glUniform4i;
extern PFNGLUNIFORM2FVPROC										glUniform2fv;
extern PFNGLUNIFORM3FVPROC										glUniform3fv;
extern PFNGLUNIFORM4FVPROC										glUniform4fv;
extern PFNGLUNIFORMMATRIX2FVPROC								glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC								glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC								glUniformMatrix4fv;
extern PFNGLBLENDFUNCSEPARATEPROC								glBlendFuncSeparate;
extern PFNGLFOGCOORDFPROC										glFogCoordf;
extern PFNGLFOGCOORDFVPROC										glFogCoordfv;
extern PFNGLFOGCOORDDPROC										glFogCoordd;
extern PFNGLFOGCOORDDVPROC										glFogCoordddv;
extern PFNGLGENBUFFERSPROC										glGenBuffers;
extern PFNGLBINDBUFFERPROC										glBindBuffer;
extern PFNGLBUFFERDATAPROC										glBufferData;
extern PFNGLBUFFERSUBDATAPROC									glBufferSubData;
extern PFNGLDELETEBUFFERSPROC									glDeleteBuffers;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC							glCompressedTexImage2D;
extern PFNGLDRAWBUFFERSPROC										glDrawBuffers;


/*
=========================================================================================================

		WGL EXTENSIONS

=========================================================================================================
*/
/* WGL_ARB_extensions_string */
extern PFNWGLGETEXTENSIONSSTRINGARBPROC							wglGetExtensionsStringARB;
/* WGL_ARB_pixelformat */
extern PFNWGLCHOOSEPIXELFORMATARBPROC							wglChoosePixelFormatARB;

/* WGL_EXT_swap_control */
extern PFNWGLSWAPINTERVALEXTPROC								wglSwapIntervalEXT;


/*
=========================================================================================================

		GL EXTENSIONS

=========================================================================================================
*/
/* GL_EXT_frambuffer_blit */
extern PFNGLBLITFRAMEBUFFEREXTPROC								glBlitFramebufferEXT;

/* GL_EXT_framebuffer_multisample */
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC				glRenderbufferStorageMultisampleEXT;

/* GL_EXT_blend_minmax */
extern PFNGLBLENDEQUATIONEXTPROC								glBlendEquationEXT;

/* GL_ARB_vertex_shader */
extern PFNGLVERTEXATTRIB3FPROC									glVertexAttrib3fARB;
extern PFNGLGETATTRIBLOCATIONARBPROC							glGetAttribLocationARB;
extern PFNGLVERTEXATTRIBPOINTERARBPROC						    glVertexAttribPointerARB;
extern PFNGLENABLEVERTEXATTRIBARRAYARBPROC						glEnableVertexAttribArrayARB;
extern PFNGLDISABLEVERTEXATTRIBARRAYARBPROC						glDisableVertexAttribArrayARB;

/* GL_EXT_framebuffer_object */
extern PFNGLRENDERBUFFERSTORAGEEXTPROC							glRenderbufferStorageEXT;
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC					glGetRenderbufferParameterivEXT;
extern PFNGLISFRAMEBUFFEREXTPROC								glIsFrameBufferEXT;
extern PFNGLBINDFRAMEBUFFEREXTPROC								glBindFramebufferEXT;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC							glDeleteFramebuffersEXT;
extern PFNGLGENFRAMEBUFFERSEXTPROC								glGenFramebuffersEXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC						glCheckFramebufferStatusEXT;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC							glFramebufferTexture1DEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC							glFramebufferTexture2DEXT;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC							glFramebufferTexture3DEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC						glFramebufferRenderbufferEXT;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC			glGetFramebufferAttachmentParameterivEXT;
extern PFNGLGENRENDERBUFFERSEXTPROC								glGenRenderbuffersEXT;
extern PFNGLDELETERENDERBUFFERSEXTPROC							glDeleteRenderbuffersEXT;
extern PFNGLBINDRENDERBUFFEREXTPROC								glBindRenderbufferEXT;
extern PFNGLISRENDERBUFFEREXTPROC								glIsRenderbufferEXT;

#endif