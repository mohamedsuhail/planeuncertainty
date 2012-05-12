#include <d3dx9.h>
#include <d3d9.h>

class Sprite
{
public:
	bool Init( IDirect3DDevice9* d3d_device );
	void Draw( D3DXVECTOR3 v3ScreenPosition );
	bool LoadTexture( const char* pFileName, IDirect3DDevice9* d3d_device );
	LPDIRECT3DTEXTURE9 m_d3dTexture;
	LPD3DXSPRITE m_d3dSprite;
};