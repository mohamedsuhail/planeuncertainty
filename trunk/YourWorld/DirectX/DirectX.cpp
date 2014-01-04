#include "DirectX.h"

#define HRESULT_CODE(hr)    ((hr) & 0xFFFF)

DirectX DirectX::m_Singleton;

DirectX::DirectX()
{

}



DirectX* DirectX::Singleton()
{
	return &m_Singleton;
}

void DirectX::Init()
{
	m_Camera.Reset();
}

bool DirectX::InitD3D(HWND hWnd, UINT uiWidth, UINT uiHeight)
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));    // clear out the struct for use
	m_d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	m_d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	m_d3dpp.BackBufferWidth = uiWidth;    // set the width of the buffer
	m_d3dpp.BackBufferHeight = uiHeight;    // set the height of the buffer

	// create a device class using this information and information from the d3dpp stuct
	if( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT
							, D3DDEVTYPE_HAL
							, hWnd
							, D3DCREATE_SOFTWARE_VERTEXPROCESSING
							, &m_d3dpp
							, &m_d3ddev) != S_OK)
	{
		return false;
	}


	D3DVERTEXELEMENT9 decl[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		//{ 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		D3DDECL_END( )
	};

	if( m_d3ddev->CreateVertexDeclaration(decl,&m_declaration) != S_OK)
	{
		return false;
	}
	return true;
}

struct CUSTOMVERTEX
{
	float x, y, z, nx, ny, nz;    // from the D3DFVF_XYZRHW flag
};

void DirectX::render_frame()
{
	CUSTOMVERTEX OurVertices[] =
	{
		{0.0f, 0.0f, 0.0f,  0,1,0},
		{0.5f, 1.0f, 0.0f, 0,1,0},
		{1.0f, 0.0f, 0.0f, 0,1,0},
	};
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL; 
	// create a vertex buffer interface called v_buffer
	HRESULT res = m_d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),
		0,
		0,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	res = v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, OurVertices, sizeof(OurVertices));
	v_buffer->Unlock();

	
	m_d3ddev->SetVertexDeclaration(m_declaration);
	m_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	m_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	m_d3ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	// clear the window to a deep blue
	m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	m_d3ddev->BeginScene();    // begins the 3D scene
	// select the vertex buffer to display
	m_d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

	D3DXMATRIX WVP;
	WVP = m_Camera.BuildViewMatrix() * BuildProjectionMatrix();
	m_SimpleSurfaceShader.Effect->SetMatrix(m_SimpleSurfaceShader.Handles.WVPmtx, &WVP);
	m_SimpleSurfaceShader.Effect->Begin(0,0);
	m_SimpleSurfaceShader.Effect->BeginPass(0);
	// copy the vertex buffer to the back buffer
	res = m_d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	m_SimpleSurfaceShader.Effect->EndPass();
	m_SimpleSurfaceShader.Effect->End();

	// do 3D rendering on the back buffer here
	m_d3ddev->EndScene();    // ends the 3D scene

	m_d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}

// this is the function that cleans up Direct3D and COM
void DirectX::cleanD3D(void)
{
	m_d3ddev->Release();    // close and release the 3D device
	m_d3d->Release();    // close and release Direct3D
}
bool DirectX::LoadShaders()
{
	if( D3DXCreateEffectFromFile(m_d3ddev,L"../DirectX/SimpleSurface.fx",0,0,D3DXSHADER_DEBUG,0,&m_SimpleSurfaceShader.Effect,0) != S_OK)
	{
		LOG(L"Failed to load SimpleSurface");
		return false;
	}
	m_SimpleSurfaceShader.Handles.WVPmtx = m_SimpleSurfaceShader.Effect->GetParameterByName(0,"WorldViewProj");
	m_SimpleSurfaceShader.Handles.Technique = m_SimpleSurfaceShader.Effect->GetTechniqueByName("tech0");
	m_SimpleSurfaceShader.Effect->SetTechnique(m_SimpleSurfaceShader.Handles.Technique);
	return true;
}


D3DXMATRIX DirectX::BuildProjectionMatrix()
{
	D3DXMATRIX Projection;
	float width = (float)m_d3dpp.BackBufferWidth;
	float height = (float)m_d3dpp.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&Projection,D3DX_PI * 0.25f,width/height,1.0f,1024.0f);
	return Projection;
}