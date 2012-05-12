#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <assert.h>
#include "../Renderer/Renderer.h"
HWND hwnd;
WNDCLASSEX the_wndclass;
HINSTANCE the_hinstance;
float app_scale_x, app_scale_y;

IDirect3D9 *d3d_object;
IDirect3DDevice9 *d3d_device;
Renderer m_Renderer;


/******************************************************************
*                                                                 *
*  WndProc                                                        *
*                                                                 *
*  Window message handler                                         *
*                                                                 *
******************************************************************/
LRESULT CALLBACK MessageProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_SIZE:
		{
			m_Renderer.WindowResize( hwnd );
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 1;
	}

	return DefWindowProc(
		hwnd,
		message,
		wParam,
		lParam
		);
}



/******************************************************************
*                                                                 *
*  DemoApp::RunMessageLoop                                        *
*                                                                 *
*  Main window message loop                                       *
*                                                                 *
******************************************************************/
void run_message_loop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		m_Renderer.Draw( hwnd );
	}
}


void register_window_class(LPCSTR winclass_name) 
{
	WNDCLASSEX wcl = { sizeof(WNDCLASSEX), CS_CLASSDC, MessageProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		winclass_name, NULL };
	the_wndclass = wcl;

	the_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	int success = RegisterClassEx(&the_wndclass);
	assert(success);
}

bool initialize() 
{
	HRESULT hr;

	LPCSTR name = "PlaneUncertainty";

	register_window_class(name);

	m_Renderer.Init( hwnd, name,  the_hinstance);


	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	return true;
}


/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{
	the_hinstance = hInstance;

	initialize();
	run_message_loop();

	return 0;
}