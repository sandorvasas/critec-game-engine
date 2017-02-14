#include "main.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	GameLocal->HandleMessage(msg, wParam, lParam);

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	WNDCLASSEX wc;
	MSG msg;

	bool running = true;

	wc.cbClsExtra			= 0;
	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.cbWndExtra			= 0;
	wc.hbrBackground		= (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hCursor				= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon				= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm				= LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance			= GetModuleHandle(0);
	wc.lpfnWndProc			= WindowProc;
	wc.lpszClassName		= "Critec";
	wc.lpszMenuName			= NULL;
	wc.style				= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClassEx(&wc);

	GameLocal = new crGameLocal();
	GameLocal->Initialize( "Critec" );

	while(running) {
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(!GameLocal->IsRunning()) 
				running = false;
		}
		else {
			GameLocal->UpdateApp();
		}
	}

	delete GameLocal;

	return (int)(msg.wParam);
}

