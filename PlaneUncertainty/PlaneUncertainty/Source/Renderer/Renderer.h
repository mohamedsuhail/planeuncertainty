#include <windows.h>
#include <d3d9.h>

#include "Sprite.h"

class Renderer
{
public:
	bool Init( HWND & hwnd, LPCSTR name, HINSTANCE the_hinstance );

	void fill_out_present(D3DPRESENT_PARAMETERS *present, HWND & hwnd) ;

	void WindowResize( HWND & hwnd );

	bool Draw( HWND & hwnd );
	void draw_line(float x0, float y0, float x1, float y1, unsigned long color);
	void rendering_2d(int width, int height);


	void DebugCrap();

	IDirect3D9 *d3d_object;
	IDirect3DDevice9 *d3d_device;
	float m_fAppscaleX;
	float m_fAppscaleY;


	//DEBUG
	Sprite m_Sprite;
};