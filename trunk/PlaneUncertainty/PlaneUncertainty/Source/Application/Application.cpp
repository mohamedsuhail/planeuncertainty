#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <assert.h>
#include "Resource.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "Renderer/Renderer.h"
#include "Time/GameTime.h"

class Application
{
public:
	static LRESULT CALLBACK MessageProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void run_message_loop();
	void register_window_class(LPCSTR winclass_name);
	bool initialize();
	void Destroy();

	HWND hwnd;
	WNDCLASSEX the_wndclass;
	HINSTANCE the_hinstance;

	Renderer m_Renderer;
	static Application* m_Singleton;
	bool m_bActive;

};
Application* Application::m_Singleton;

/******************************************************************
*                                                                 *
*  WndProc                                                        *
*                                                                 *
*  Window message handler                                         *
*                                                                 *
******************************************************************/
LRESULT CALLBACK Application::MessageProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MOVE:
	case WM_SIZE:
		{
			m_Singleton->m_Renderer.DeviceLost( hwnd );
		}
		break;
	case WM_DESTROY:
		{
			m_Singleton->m_bActive = false;
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
void Application::run_message_loop()
{
	MSG msg;

	m_bActive = true;

	while ( m_bActive )
	{
		if(PeekMessage(&msg, NULL, 0, 0, 1 ) )
		{
			DispatchMessage(&msg);
			TranslateMessage(&msg);
		}
 		m_Renderer.Draw( hwnd );
		GameTime::Update();
	}
	Destroy();
}


void Application::register_window_class(LPCSTR winclass_name) 
{
	WNDCLASSEX wcl = { sizeof(WNDCLASSEX), CS_CLASSDC, Application::MessageProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		winclass_name, NULL };
	the_wndclass = wcl;

	the_wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	int success = RegisterClassEx(&the_wndclass);
	assert(success);
}

bool Application::initialize() 
{
	HRESULT hr;

	LPCSTR name = "PlaneUncertainty";

	register_window_class(name);

	m_Renderer.Init( hwnd, name,  the_hinstance);


	ShowWindow(hwnd, SW_SHOWNORMAL);
	ShowCursor( true );
	UpdateWindow(hwnd);

	return true;
}

void Application::Destroy()
{
	m_Renderer.Destroy();
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
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	Application App;

	Application::m_Singleton = &App;

	App.the_hinstance = hInstance;
	App.initialize();
	

	App.run_message_loop();
	
	_CrtDumpMemoryLeaks();

	return 0;
}