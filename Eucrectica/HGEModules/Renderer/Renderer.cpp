#include "Renderer.h"
#include "../Haaf/include/hgefont.h"

namespace HGE_Modules
{
	Renderer::Renderer(): m_pHGE(NULL)
		, m_pFont(NULL)
		, m_iSpriteIndex(0)
		, m_iAnimationIndex(0)
		, m_v2CameraPosition( Maths::Vector<2>(0,0))
	{

	}

	void Renderer::Init( HGE* pHGE, const char* RootDir )
	{
		m_pHGE = pHGE;
		strncpy_s( m_RootDir, RootDir, s_iStringLength );
		m_iSpriteIndex = 0;
		m_iAnimationIndex = 0;
		m_v2CameraPosition = Maths::Vector<2>(0,0);
	}

	int Renderer::LoadSprite( const char* FileName, Maths::Vector<2> v2SpriteDimensions )
	{
		//add the root filepath to the filename
		char filepath[s_iStringLength];
		strncpy_s( filepath,m_RootDir, s_iStringLength );
		strcat_s( filepath, s_iStringLength, FileName );

		//store the unique ID to return
		int iID( m_iSpriteIndex++ );

		//create and load the sprite
		SpriteInVec Sprite;
		HTEXTURE Texture( LoadTexture(filepath) );
		Sprite.m_pSprite = new hgeSprite( Texture, 0, 0, v2SpriteDimensions[0], v2SpriteDimensions[1] );

		//set the texture rect to the default frame
		Sprite.m_pSprite->SetTextureRect( 0, 0, v2SpriteDimensions[0], v2SpriteDimensions[1] );

		Sprite.m_iID = iID;
		m_SpriteVector.push_back( Sprite );
		return iID;
	}

	HTEXTURE Renderer::LoadTexture( const char* Filename )
	{
		TextureVector::iterator TextureIter( std::find( m_Textures.begin(), m_Textures.end(), Filename ) );
		if( TextureIter == m_Textures.end() )
		{
			HTEXTURE texture( m_pHGE->Texture_Load(&Filename[0]) );

			if( !texture )
			{
				char error[s_iStringLength];
				strncpy_s( error, "Can't load: ", s_iStringLength );
				strcat_s( error, s_iStringLength, Filename );
				MessageBox(NULL, error, "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			}

			m_Textures.push_back( LoadedTexture( texture, Filename) );
			return texture;
		}
		else
		{
			return (*TextureIter).m_Texture;
		}
	}

	void Renderer::LoadFont( const char* FileName )
	{
		char filepath[s_iStringLength];
		strncpy_s( filepath,m_RootDir, s_iStringLength );
		strcat_s( filepath, s_iStringLength, FileName );
		m_pFont=new hgeFont( filepath );
	}

	int Renderer::LoadAnimation( const char* FileName, Maths::Vector<2> v2FrameDimensions, int iDuration, bool bRepeating /*=true*/ )
	{

		char filepath[s_iStringLength];
		strncpy_s( filepath,m_RootDir, s_iStringLength );
		strcat_s( filepath, s_iStringLength, FileName );
		HTEXTURE texture( LoadTexture(filepath) );
		int iID( m_iAnimationIndex++ );
		AnimationInVec animation;
		animation.m_Animation.Construct( m_pHGE, v2FrameDimensions[0], v2FrameDimensions[1], texture, iDuration, bRepeating );
		animation.m_iID = iID;
		m_AnimationVector.push_back( animation );
		return iID;
	}

	float Renderer::BeginScene()
	{
		// Render graphics
		m_pHGE->Gfx_BeginScene();
		m_pHGE->Gfx_Clear(0);
		//m_pFont->printf( 5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", m_pHGE->Timer_GetDelta(), m_pHGE->Timer_GetFPS() );
		m_pFont->printf( 20, 5, HGETEXT_LEFT, "FPS:%d (constant)",  m_pHGE->Timer_GetFPS() );
		return m_pHGE->Timer_GetDelta();
	}

	void Renderer::EndScene()
	{
		m_pHGE->Gfx_EndScene();
	}

	void Renderer::UnloadAll()
	{
		for( TextureVector::iterator iter( m_Textures.begin() ), endIter( m_Textures.end() );
			iter != endIter;
			++iter)
		{
			m_pHGE->Texture_Free( (*iter).m_Texture );
		}
		for( SpriteVector::iterator iter( m_SpriteVector.begin() ), endIter( m_SpriteVector.end() );
			iter != endIter;
			++iter )
		{
			delete( (*iter).m_pSprite );
		}
		for( AnimationVector::iterator iter( m_AnimationVector.begin()), endIter( m_AnimationVector.end() );
			iter != endIter;
			++iter )
		{
			(*iter).m_Animation.Clear();
		}
		m_SpriteVector.clear();
		m_AnimationVector.clear();
		delete m_pFont;
	}

	void Renderer::Destroy()
	{
		UnloadAll();
	}

	void Renderer::DrawSprite( int iID, Maths::Vector<2> v2Position, float fDepth )
	{
		for( SpriteVector::iterator iter( m_SpriteVector.begin() ), endIter( m_SpriteVector.end() );
			iter != endIter;
			++iter )
		{
			if( (*iter).m_iID == iID )
			{
				v2Position -= m_v2CameraPosition;
				(*iter).m_pSprite->SetZ( fDepth );
				(*iter).m_pSprite->SetColor(ARGB(100,255,255,255));
				(*iter).m_pSprite->Render( v2Position[0],v2Position[1] );
			}

		}
	}

	void Renderer::DrawSpritePartial( int iID, Maths::Vector<2> v2Position, float fDepth, float fWidthPercentage, float fHeightPercentage )
	{
		for( SpriteVector::iterator iter( m_SpriteVector.begin() ), endIter( m_SpriteVector.end() );
			iter != endIter;
			++iter )
		{
			if( (*iter).m_iID == iID )
			{
				v2Position -= m_v2CameraPosition;
				(*iter).m_pSprite->SetZ( fDepth );
				float fOriginalTextureRect[4];
				(*iter).m_pSprite->GetTextureRect( &fOriginalTextureRect[0], &fOriginalTextureRect[1], 
					&fOriginalTextureRect[2], &fOriginalTextureRect[3] );
				(*iter).m_pSprite->SetTextureRect( 0, 0, 
					( fOriginalTextureRect[2] / 100.0f ) * fWidthPercentage, 
					( fOriginalTextureRect[3] / 100.0f ) * fHeightPercentage );

				(*iter).m_pSprite->Render( v2Position[0],v2Position[1] );
				(*iter).m_pSprite->SetTextureRect( fOriginalTextureRect[0], fOriginalTextureRect[1], 
					fOriginalTextureRect[2], fOriginalTextureRect[3] );
			}

		}
	}

	void Renderer::DrawAnimation( int iID, Maths::Vector<2> v2Position, float fDepth, float fRunTime )
	{
		for( AnimationVector::iterator iter( m_AnimationVector.begin() ), endIter( m_AnimationVector.end());
			iter != endIter;
			++iter )
		{
			if( (*iter).m_iID == iID )
			{
				v2Position -= m_v2CameraPosition;
				(*iter).m_Animation.Render( fRunTime, v2Position, fDepth );
			}
		}
	}

	void Renderer::DrawAnimationFrame( int iID, Maths::Vector<2> v2Position, float fDepth, int iFrame )
	{
		for( AnimationVector::iterator iter( m_AnimationVector.begin() ), endIter( m_AnimationVector.end());
			iter != endIter;
			++iter )
		{
			if( (*iter).m_iID == iID )
			{
				v2Position -= m_v2CameraPosition;
				(*iter).m_Animation.Render( iFrame, v2Position, fDepth );
			}
		}
	}

	void Renderer::SetCameraPosition( Maths::Vector<2> v2Position )
	{
		m_v2CameraPosition = v2Position;
	}

	Maths::Vector<2> Renderer::GetCameraPosition()
	{
		return m_v2CameraPosition;
	}
}
