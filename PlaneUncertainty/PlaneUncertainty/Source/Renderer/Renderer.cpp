#include "Renderer.h"



void Renderer::DebugCrap()
{
	m_Sprite.Init(d3d_device);
	bool worked = m_Sprite.LoadTexture( "Resources\\Textures\\Knight_Sprite_Sheet.png", d3d_device );
}



bool Renderer::Init( HWND & hwnd, LPCSTR name, HINSTANCE the_hinstance )
{
	// Get desktop DPI.
	HDC screen = GetDC(0);
	m_fAppscaleX = (float)(GetDeviceCaps(screen, LOGPIXELSX) / 96.0);
	m_fAppscaleY = (float)(GetDeviceCaps(screen, LOGPIXELSX) / 96.0);
	ReleaseDC(0, screen);

	int width = (int)(1280 * m_fAppscaleX);
	int height = (int)(720 * m_fAppscaleY);

	hwnd = CreateWindow(
		name,
		name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		the_hinstance,
		NULL
		);

	d3d_object = Direct3DCreate9(D3D_SDK_VERSION);

	// Fill out the presentation parameters for the D3D device... windowed mode.
	D3DPRESENT_PARAMETERS present;
	
	fill_out_present(&present, hwnd);

	UINT AdapterToUse = D3DADAPTER_DEFAULT;
	D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
	d3d_object->CreateDevice(AdapterToUse, DeviceType, hwnd,
		D3DCREATE_FPU_PRESERVE | D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&present, &d3d_device);

	if (!d3d_device) 
	{
		return false;
	}

	DebugCrap();
	

	return true;
}


// Fill the struct that tells D3D how to set up buffers and page flip.
void Renderer::fill_out_present(D3DPRESENT_PARAMETERS *present, HWND & hwnd) 
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	ZeroMemory(present, sizeof(*present));

	present->Windowed = TRUE;
	present->MultiSampleType = D3DMULTISAMPLE_NONE;
	present->SwapEffect = D3DSWAPEFFECT_DISCARD;
	present->EnableAutoDepthStencil = FALSE;
	present->BackBufferFormat = D3DFMT_A8R8G8B8;
	present->hDeviceWindow = hwnd;
	present->Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	present->BackBufferCount = 1;
	present->BackBufferWidth = width;
	present->BackBufferHeight = height;
	present->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void Renderer::DeviceLost( HWND & hwnd )
{
	if (d3d_device) 
	{
		D3DPRESENT_PARAMETERS present;
		fill_out_present(&present, hwnd);
		if (present.BackBufferWidth && present.BackBufferHeight) 
		{
			d3d_device->Reset(&present);
			InvalidateRect(hwnd, NULL, FALSE);
		}
		//destroy then reset sprites!!!
		m_Sprite.Destroy();
		DebugCrap();
	}
}


struct Line_Vertex {
	float x, y, z;
	unsigned long color;
};


void Renderer::draw_line(float x0, float y0, float x1, float y1, unsigned long color) {
	Line_Vertex vertices[2];

	vertices[0].x = x0;
	vertices[0].y = y0;
	vertices[0].z = 0;
	vertices[0].color = color;

	vertices[1].x = x1;
	vertices[1].y = y1;
	vertices[1].z = 0;
	vertices[1].color = color;

	HRESULT hr = d3d_device->DrawPrimitiveUP(D3DPT_LINELIST, 1,
		vertices, sizeof(Line_Vertex));
}

//
// rendering_2d() sets the Direct3D transformation matrix for 2D rendering.
// In an API geared toward 2D rendering you could probably just delete this function.
//
void Renderer::rendering_2d(int width, int height) {
	D3DMATRIX m;
	memset(&m, 0, sizeof(D3DMATRIX));

	m._11 = 2.0f * m_fAppscaleX / (float)width;
	m._41 = -1.0f * m_fAppscaleX;
	m._22 = 2.0f * m_fAppscaleY / (float)height;
	m._42 = -1.0f * m_fAppscaleY;

	m._33 = 1;
	m._43 = 0;

	m._34 = 0;
	m._44 = 1;

	d3d_device->SetTransform(D3DTS_PROJECTION, &m);
}

// Put points into a 4-element vertex buffer.
void make_rectangle_points(Line_Vertex *p, float center_x, float center_y, float width, unsigned long color) 
{
	p[0].x = p[3].x = center_x - width;
	p[1].x = p[2].x = center_x + width;

	p[0].y = p[1].y = center_y - width;
	p[2].y = p[3].y = center_y + width;

	p[0].z = p[1].z = p[2].z = p[3].z = 0;
	p[0].color = p[1].color = p[2].color = p[3].color = color;
}

bool Renderer::Draw( HWND & hwnd ) 
{
	if (!d3d_device) return false;  // Haven't been initialized yet!

	HRESULT result = d3d_device->BeginScene();
	if (result != D3D_OK) return false;

	unsigned long clear_color = 0xffffffff;
	d3d_device->Clear(0, NULL, D3DCLEAR_TARGET, clear_color,
		1.0f, 0);

	d3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	d3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3d_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	d3d_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	RECT rect;
	GetClientRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;


	rendering_2d(width, height);


	// Draw a grid background.
	unsigned long line_color = 0xffd0d0d0;
	for (int i = 0; i < width; i += 5) {
		draw_line(i, 0, i, height, line_color);
	}

	for (int j = 0; j < height; j += 5) {
		draw_line(0, j, width, j, line_color);
	}


	float center_x = width * 0.5f;
	float center_y = height * 0.5f;

	Line_Vertex p[5];

	// Draw the solid rectangle.
	unsigned long solid_color = 0xff778899;
	make_rectangle_points(p, center_x, center_y, 50.0f, solid_color);
	result = d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, p, sizeof(Line_Vertex));  // Half the rectangle

	// Draw the outline rectangle.
	unsigned long outline_color = 0xffb0c7ee;
	make_rectangle_points(p, center_x, center_y, 100.0f, outline_color);
	p[4] = p[0];  // Make a closed loop.
	result = d3d_device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, p, sizeof(Line_Vertex));

	D3DXVECTOR3 vec;
	m_Sprite.Draw( vec );
	// Finish rendering; page flip.
	HRESULT hr = d3d_device->EndScene();
	hr = d3d_device->Present(NULL, NULL, NULL, NULL);


	return true;
}

void Renderer::Destroy()
{
	m_Sprite.Destroy();
	
	d3d_device->Release();
	d3d_object->Release();

}

