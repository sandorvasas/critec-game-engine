#include "OpenGLRenderDevice.h"
#include <windows.h>

int crOpenGLRenderDevice::Initialize( crInitOptions_t iOpts ) {
	InitOptions = iOpts;

	InitOptions.hDeviceContext = new HDC;
	*InitOptions.hDeviceContext = GetDC(InitOptions.hWindow);

	PIXELFORMATDESCRIPTOR Pfd;

	ZeroMemory(&Pfd, sizeof(PIXELFORMATDESCRIPTOR));
	Pfd.nSize	   = sizeof(PIXELFORMATDESCRIPTOR);
	Pfd.nVersion   = 1;
	Pfd.iLayerType = PFD_MAIN_PLANE;
	Pfd.cDepthBits = iOpts.iDepthBits;
	Pfd.cAlphaBits = iOpts.iAlphaBits;
	Pfd.cColorBits = iOpts.iColorBits;
	Pfd.iPixelType = PFD_TYPE_RGBA;
	Pfd.dwFlags	   = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;

	int pf = 0;

//============================================================================================ 
// Commented, because wglGetProcAddress cannot find the address of wglChoosePixelFormatARB
//============================================================================================
	/*if (InitOptions.iMultiSampling) {

		unsigned int numformats = 0;
		float fAttribs[] = {0,0};
		int iAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, iOpts.iColorBits,
			WGL_DEPTH_BITS_ARB, iOpts.iDepthBits,
			WGL_STENCIL_BITS_ARB, iOpts.iStencilBits,
			WGL_ALPHA_BITS_ARB, iOpts.iAlphaBits,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, iOpts.iMultiSampling,
			0,0
		};
		LoadEXT_wglChoosePixelFormatARB();
		wglChoosePixelFormatARB(InitOptions.hDeviceContext, iAttribs, fAttribs, 1, &pf, &numformats);

		if (numformats <= 1) {
			InitOptions.iMultiSampling = 0;
			pf = ChoosePixelFormat( InitOptions.hDeviceContext, &Pfd );
		}

	} else*/
//============================================================================================ 
// End of Commented Section
//============================================================================================
		pf = ChoosePixelFormat( *InitOptions.hDeviceContext, &Pfd );

	SetPixelFormat(*InitOptions.hDeviceContext, pf, &Pfd);

	hRenderContext = wglCreateContext(*InitOptions.hDeviceContext);
	wglMakeCurrent(*InitOptions.hDeviceContext, hRenderContext);

	if(!Initialized) LoadOpenGLCore();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );

	if(iOpts.bVSync && LoadEXT_WGL_EXT_swap_control()) wglSwapIntervalEXT( 1 );

	Initialized = true;

	return 0;
}

void crOpenGLRenderDevice::HandleError( int ErrorCode ) {
	/*switch( ErrorCode ) {
	}*/
}

void crOpenGLRenderDevice::Shutdown( void ) {
	 wglDeleteContext( hRenderContext );
	 if(InitOptions.hDeviceContext) {
		ReleaseDC( InitOptions.hWindow, *InitOptions.hDeviceContext );
		delete InitOptions.hDeviceContext;
	 }
	Initialized = false;
}

void crOpenGLRenderDevice::SwapBuffers( void ) {
	::SwapBuffers( *InitOptions.hDeviceContext );
}

void crOpenGLRenderDevice::SetPerspective( crProjAttribs_t projAttr ) {
	this->ProjAttribs = projAttr;
	float f = float( 1/tanf( float(projAttr.FieldOfView) / 2.f ) );
	float a = float( f/projAttr.AspectRatio );
	float d = float( (projAttr.nearPlane + projAttr.farPlane) / (projAttr.nearPlane - projAttr.farPlane) );
	float g = float( (2*projAttr.nearPlane*projAttr.farPlane)/ (projAttr.nearPlane - projAttr.farPlane) );

	crMat4 PersMatrix = 
		crMat4 (a,			0.f,		0.f,		0.f,
				0.f,		f,			0.f,		0.f,
				0.f,		0.f,		d,			g,
				0.f,		0.f,		-1.f,		0.f	);
							
	glMatrixMode( GL_PROJECTION );
	SetTransform(TRANSFORM_LOAD, PersMatrix.ToFloatPtr());
	glMatrixMode( GL_MODELVIEW );
} 

void crOpenGLRenderDevice::SetOrtho( bool ortho ) {
	if (ortho)	{
		glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glOrtho(-1.0, 1.0, 1.0, -1.0, -1.0, 1.0);
				glLoadIdentity();
				glPushMatrix();
	} else {
				glPopMatrix();
			glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
}

void crOpenGLRenderDevice::SetTransform( int transformId, float* matrix ) {
	switch(transformId) {
		case TRANSFORM_LOAD: glLoadMatrixf(matrix);
		break;

		case TRANSFORM_MULT: glMultMatrixf(matrix);
		break;

		case TRANSFORM_SCALE: glMultMatrixf( crMat4(matrix[0], 0, 0, 0, 
													0, matrix[1], 0, 0,
													0, 0, matrix[2], 0,
													0, 0,  0, 0 ).ToFloatPtr());
		break;

		case TRANSFORM_TRANSLATE: glMultMatrixf( crMat4(1, 0, 0, 0, 
														0, 1, 0, 0,
														0, 0, 1, 0,
														matrix[0], matrix[1], matrix[2], 0 ).ToFloatPtr());
		break;

		case TRANSFORM_ROTATE: 
			crMat4 mat;
			mat.Rotate(matrix[0], matrix[1], matrix[2]);
			glMultMatrixf( mat.ToFloatPtr() );
		break;
	}
}

void crOpenGLRenderDevice::LoadIdentity( void ) {
	glLoadIdentity();
}

void crOpenGLRenderDevice::DrawSquare( crVec3 p1, crVec3 p2, int texUnit ) {
	glBegin(GL_QUADS);
		glMultiTexCoord2f(GL_TEXTURE0+texUnit, 0.f, 0.f); glVertex3fv( p1.ToFloatPtr() );
		glMultiTexCoord2f(GL_TEXTURE0+texUnit, 1.f, 0.f); glVertex3f(  p1.x, p2.y, p2.z );
		glMultiTexCoord2f(GL_TEXTURE0+texUnit, 1.f, 1.f); glVertex3fv( p2.ToFloatPtr() );
		glMultiTexCoord2f(GL_TEXTURE0+texUnit, 0.f, 1.f); glVertex3f(  p2.x, p1.y, p1.z );
	glEnd();
}

void crOpenGLRenderDevice::DrawBox( crVec3 p1, crVec3 p2, int texUnit ) {
	// front and back 
	DrawSquare( crVec3( p1.x, p1.y, p1.z ), crVec3( p2.x, p2.y, p1.z ), texUnit );
	DrawSquare( crVec3( p1.x, p1.y, p2.z ), crVec3( p2.x, p2.y, p2.z ), texUnit );
	//left and right
	DrawSquare( crVec3( p1.x, p1.y, p1.z ), crVec3( p1.x, p2.y, p2.z ), texUnit );
	DrawSquare( crVec3( p2.x, p1.y, p1.z ), crVec3( p2.x, p2.y, p2.z ), texUnit );
	//top and bottom
	DrawSquare( crVec3( p1.x, p1.y, p1.z ), crVec3( p2.x, p1.y, p2.z ), texUnit );
	DrawSquare( crVec3( p2.x, p2.y, p2.z ), crVec3( p2.x, p2.y, p2.z ), texUnit );
}

void crOpenGLRenderDevice::DrawSprite( crVec2 p1, crVec2 p2, unsigned int texture ) {
	SetOrtho( true );

		glAlphaFunc(GL_GREATER, 0.6f);
		glEnable(GL_ALPHA_TEST);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		DrawSquare( crVec3(p1, 0.2f), crVec3(p2, 0.2f), 0 );

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_ALPHA_TEST);
	SetOrtho( false );
}

void crOpenGLRenderDevice::DrawPoint( crVec3 pos, float r, float g, float b ) {
	glColor3f( r, g, b );
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos.ToFloatPtr());
	glEnd();
	glPointSize(1.0f);
	glColor3f( 1.0f, 1.0f, 1.0f );
}

crMat4 crOpenGLRenderDevice::GetModelViewMatrix( void ) {
	float matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	return crMat4(matrix);
}

crMat4 crOpenGLRenderDevice::GetProjectionMatrix( void ) {
	float matrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	return crMat4(matrix);
}

crMat4 crOpenGLRenderDevice::GetTextureMatrix( void ) {
	float matrix[16];
	glGetFloatv(GL_TEXTURE_MATRIX, matrix);
	return crMat4(matrix);
}