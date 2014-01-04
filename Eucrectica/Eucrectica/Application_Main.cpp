#include "../Haaf/include/hge.h"
#include "../HGEModules/Renderer/Renderer.h"
#include "../HGEModules/Input/Input.h"


namespace
{
	HGE* _pHGE = NULL;
	HGE_Modules::Renderer _Renderer;
	HGE_Modules::Input _Input;
}

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
bool FrameFunc()
{
	//Update Input, if it returns true the game exit command has been given
	if( _Input.Update() )
	{
		return true;
	}

	// Continue execution
	return false;
}


bool RenderFunc()
{
	static float time = 0;
	time +=_Renderer.BeginScene();
	
	_Renderer.DrawSpritePartial(0,Maths::Vector<2>(0,256), 1, 25, 50);

	//_Renderer.DrawAnimationFrame(0, Vector<2>();

	_Renderer.DrawAnimation(0, Maths::Vector<2>(0,0),0.5f,time);
	_Renderer.DrawSprite(0, Maths::Vector<2>(0,0), 1);
	_Renderer.EndScene();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	_pHGE = hgeCreate(HGE_VERSION);
	
	_pHGE ->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	_pHGE->System_SetState(HGE_TITLE, "Eucrectica");

	_pHGE->System_SetState(HGE_WINDOWED, true);
	_pHGE->System_SetState(HGE_USESOUND, true);


	_pHGE->System_SetState(HGE_LOGFILE, "Eucrectica.log");
	_pHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
	_pHGE->System_SetState(HGE_FPS, 60);
	_pHGE->System_SetState(HGE_WINDOWED, true);
	_pHGE->System_SetState(HGE_SCREENWIDTH, 800);
	_pHGE->System_SetState(HGE_SCREENHEIGHT, 600);
	_pHGE->System_SetState(HGE_SCREENBPP, 32);
	
	
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	if(_pHGE->System_Initiate())
	{
		_Renderer.Init( _pHGE, "../Content/Sprites/");
		_Renderer.LoadSprite( "Mud_Tiles.png", Maths::Vector<2>(128, 128) );
		int x = _Renderer.LoadAnimation( "Walk_Second_128.png", Maths::Vector<2>(128, 256), 1000, true );
		_Renderer.LoadFont( "font1.fnt" );

		_Input.Init( _pHGE );

		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		_pHGE->System_Start();
	}
	else
	{	
		// If HGE initialization failed show error message
		MessageBox(NULL, _pHGE->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.
	_Renderer.Destroy();
	// Restore video mode and free
	// all allocated resources
	_pHGE->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	_pHGE->Release();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	
	return 0;
}

