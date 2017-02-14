// C by sonka
#ifndef __CRITEC_APPLICATION_H__
#define __CRITEC_APPLICATION_H__

#include <windows.h>
#include "../Renderer/OpenGLRenderDevice.h"
#pragma hdrstop

typedef struct crWindow_s {
	char*		Title;
	const char*	ClassName;
	HWND		hDesc;
	int			x, y;
	int			iWidth;
	int			iHeight;
} crWindow_t;

/*
=================================
	crApplication
=================================
*/
class crApplication {
protected:
	float					FPS;
	double					msElapsedTime;
	crWindow_t				GameWindow;
	bool					Running;
	bool					Keys[256];
	float					frametime;

public:
							crApplication( void );
	virtual					~crApplication( void );

	void					CreateGameWindow( void );
	void					DestroyGameWindow( void );

	void					DefaultHandleMessage( unsigned int, WPARAM, LPARAM );
	void					DefaultUpdateApp( void );
	void					DefaultShutdown( void );
	float					GetFPS( void );
	bool					IsRunning( void ) const;

	virtual int				Initialize( const char* wClassName ) = 0;
	virtual void			Shutdown( void ) = 0;
	virtual void			Render( void ) = 0;
	virtual void			RenderToBuffer( void ) = 0;
	virtual void			ProcessKeys( void ) = 0;
};


inline
crApplication::crApplication( void ) {
	ZeroMemory(&Keys, sizeof(Keys));
	FPS = 60.f;
	msElapsedTime = 0;
	Running = true;
	renderDevice = NULL;
}

inline 
crApplication::~crApplication( void ) {
	DefaultShutdown();
}

inline 
bool crApplication::IsRunning( void ) const {
	return Running;
}

#endif /* __CRITEC_APPLICATION_H__ */