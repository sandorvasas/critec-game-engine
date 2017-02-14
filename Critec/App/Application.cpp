#include "Application.h"

void crApplication::CreateGameWindow( void ) {
	GameWindow.hDesc = CreateWindowEx( WS_EX_APPWINDOW, 
									   GameWindow.ClassName, 
									   GameWindow.Title, WS_POPUP, 
									   GameWindow.x, GameWindow.y, 
									   GameWindow.iWidth,
									   GameWindow.iHeight, 
									   NULL, NULL, GetModuleHandle(0), NULL );
}

void crApplication::DestroyGameWindow( void ) {
	DestroyWindow(GameWindow.hDesc);
}

void crApplication::DefaultShutdown( void ) {
	if (Running && renderDevice) 
		delete renderDevice;
	Running = false;
}

void crApplication::DefaultHandleMessage( unsigned int msg, WPARAM wParam, LPARAM lParam ) {
	switch( msg ) {
		case WM_KEYDOWN: Keys[wParam] = true;
		break;

		case WM_KEYUP: Keys[wParam] = false;
		break;
	}
}

void crApplication::DefaultUpdateApp( void ) {
	ProcessKeys();
	Render();
	GetFPS();
}

float crApplication::GetFPS( void ) {
	static float counter = 0.f;
	static float lastTime = 0.f;
	counter++;

	msElapsedTime = GetTickCount();

	float now = GetTickCount()/1000.f;
	if(now - lastTime >= 1.f) {
		lastTime = now;
		FPS = counter;
		counter = 0.f;
		frametime = 1.0f / FPS;
	}

	return FPS;
}