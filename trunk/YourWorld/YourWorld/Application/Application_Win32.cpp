#include "Application_Win32.h"
#include "DirectX.h"


namespace ApplicationDefaultParameters
{
	static const UINT uiDefaultWidth = 800;
	static const UINT uiDefaultHeight = 600;
}

Application Application::m_Singleton;

void Application::Init()
{
	DirectX::Singleton()->InitD3D(m_HWND);
}



// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	Application::Singleton()->GetHWND() = CreateWindowEx(NULL,
		L"WindowClass1",    // name of the window class
		L"BuildCreateDestroy",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		100,    // x-position of the window
		100,    // y-position of the window
		ApplicationDefaultParameters::uiDefaultWidth,    // width of the window
		ApplicationDefaultParameters::uiDefaultHeight,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if( !DirectX::Singleton()->InitD3D( Application::Singleton()->GetHWND()
								 , ApplicationDefaultParameters::uiDefaultWidth
								 , ApplicationDefaultParameters::uiDefaultHeight) )
	{
		LOG(L"Failed to create D3D device");
		return 0;
	}
	if( !DirectX::Singleton()->LoadShaders() )
	{
		LOG(L"Failed to load shaders");
		DirectX::Singleton()->cleanD3D();
		return 0;
	}

	//   if( MessageBox(hWnd,
	//              L"Run Application?",
	//              L"BuildCreateDestroy",
	//              MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
	//{
	//	return 0;
	//}


	// display the window on the screen
	ShowWindow(Application::Singleton()->GetHWND(), nCmdShow);



	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	bool bRunning = true;
	while(bRunning)
	{
		// Check to see if any messages are waiting in the queue
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}

		switch(msg.message)
		{
		case WM_QUIT: bRunning = false;
			break;
		}

		// Run game code here
		// ...
		// ...
		DirectX::Singleton()->render_frame();
	}

	DirectX::Singleton()->cleanD3D();
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;

}




// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch(message)
	{
		//this message is read when the window is closed
	case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hWnd, message, wParam, lParam);
}

