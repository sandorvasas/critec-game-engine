// Copyright (C) 2007 by Sandor Vasas


#include <windows.h>
#include "Game/GameLocal.h"
#include "misc/sys.h"


crGameLocal*			GameLocal;
crOpenGLRenderDevice *	renderDevice;
LRESULT CALLBACK		WindowProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

