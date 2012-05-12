#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>
#include <d3d9.h>

class Sprite
{
	static const int s_iFileNameSize = 128;
public:
	bool Init( IDirect3DDevice9* d3d_device );
	void Draw( D3DXVECTOR3 v3ScreenPosition );
	bool LoadTexture( const char* pFileName, IDirect3DDevice9* d3d_device );
	void Destroy();

	LPDIRECT3DTEXTURE9 m_d3dTexture;
	LPD3DXSPRITE m_d3dSprite;
	int m_iTextureID;
};

#endif//SPRITE_H_