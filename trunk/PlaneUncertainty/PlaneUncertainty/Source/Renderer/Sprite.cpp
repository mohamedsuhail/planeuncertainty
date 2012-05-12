#include "Sprite.h"

void Sprite::Draw( D3DXVECTOR3 v3ScreenPosition )
{
	D3DXVECTOR3 pos;

	pos.x=10.0f;
	pos.y=20.0f;
	pos.z=0.0f;

	m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_d3dSprite->Draw( m_d3dTexture, NULL, NULL, &pos, 0xFFFFFFFF );
	m_d3dSprite->End();
}

bool Sprite::LoadTexture( const char* pFileName, IDirect3DDevice9* d3d_device  )
{
	return SUCCEEDED( D3DXCreateTextureFromFile( d3d_device, pFileName, &m_d3dTexture ) );
}

bool Sprite::Init( IDirect3DDevice9* d3d_device )
{
	return SUCCEEDED( D3DXCreateSprite(d3d_device,&m_d3dSprite) );
}