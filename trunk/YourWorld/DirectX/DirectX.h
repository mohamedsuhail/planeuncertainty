#ifndef _DIRECTX_H_
#define _DIRECTX_H_

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "Camera.h"

class DirectX
{
	static const UINT uiDefaultWidth = 800;
	static const UINT uiDefaultHeight = 600;

	struct EffectHandle
	{
		D3DXHANDLE WVPmtx;
		D3DXHANDLE Worldmtx;
		D3DXHANDLE Viewmtx;
		D3DXHANDLE InverseTransWorld;
		D3DXHANDLE InverseView;
		D3DXHANDLE LightWorldViewProj;

		D3DXHANDLE Ia;
		D3DXHANDLE Ka;
		D3DXHANDLE Kd;
		D3DXHANDLE Ili;
		D3DXHANDLE LightPos;
		D3DXHANDLE Ks;
		D3DXHANDLE SpecularPower;
		D3DXHANDLE Technique;
		D3DXHANDLE Intensity;

		D3DXHANDLE LightDirection;
		D3DXHANDLE ConeAngle;

		D3DXHANDLE ShadowMap;
		D3DXHANDLE NormalMap;
	};

	struct s_shader
	{
		ID3DXEffect* Effect;
		EffectHandle Handles;
		std::string Name;
	};

public:
	static DirectX* Singleton();
	bool InitD3D(HWND hWnd, UINT uiWidth = uiDefaultWidth, UINT uiHeight = uiDefaultHeight);
	bool LoadShaders();
	void render_frame();    // renders a single frame
	void cleanD3D();    // closes Direct3D and releases memory
	void Init();

private:
	D3DXMATRIX BuildProjectionMatrix();

private:
	static DirectX m_Singleton; //singleton
	DirectX();
	LPDIRECT3D9 m_d3d;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 m_d3ddev;    // the pointer to the device class
	D3DPRESENT_PARAMETERS m_d3dpp; // the parameter list of the d3d device
	IDirect3DVertexDeclaration9* m_declaration;
	s_shader m_SimpleSurfaceShader;
	Camera m_Camera;

	LPDIRECT3DTEXTURE9 pPyramideTexture;
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
};

#endif