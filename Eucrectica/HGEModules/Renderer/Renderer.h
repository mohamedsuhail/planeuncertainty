#pragma once
#ifndef _HGE_RENDERER_H_
#define _HGE_RENDERER_H_

#include "../Haaf/include/hge.h"
#include "../Haaf/include/hgesprite.h"

#include "../Animation/Animation.h"
#include "../Types_And_Defines/IRenderer.h"

class hgeFont;
namespace HGE_Modules
{
	class Renderer : public IRenderer
	{
		struct SpriteInVec
		{
			hgeSprite* m_pSprite;
			int m_iID;
		};

		struct AnimationInVec
		{
			Animation m_Animation;
			int m_iID;
		};

		static const int s_iStringLength = 150;
		static const int s_iMaxSprites = 50;
		static const int s_iMaxAnimations = 200;
		typedef asl::static_vector<SpriteInVec, s_iMaxSprites> SpriteVector;
		typedef asl::static_vector<AnimationInVec, s_iMaxAnimations> AnimationVector;

		struct LoadedTexture
		{
			LoadedTexture(): m_Texture( 0 )
			{

			}
			LoadedTexture( HTEXTURE Texture, const char* TextureName ): m_Texture( Texture )
			{
				strncpy_s( m_TextureName, TextureName, s_iStringLength );
			}
			HTEXTURE m_Texture;
			char m_TextureName[s_iStringLength];

			bool operator== ( const char* OtherName )
			{
				return strcmp( OtherName, m_TextureName ) == 0;
			}
		};
		typedef asl::static_vector<LoadedTexture, 500> TextureVector;
	public:
		//singleton accessor
		Renderer();
		void Init( HGE* pHGE, const char* RootDir );
		int LoadSprite( const char* FileName, Maths::Vector<2> v2FrameDimensions );
		int LoadAnimation( const char* FileName, Maths::Vector<2> v2FrameDimensions, int iDuration, bool bRepeating = true );
		void LoadFont( const char* FileName );
		float BeginScene();
		void EndScene();
		void DrawSprite( int iID, Maths::Vector<2> v2Position, float fDepth );
		void DrawSpritePartial( int iID, Maths::Vector<2> v2Position, float fDepth, float fWidthPercentage, float fHeightPercentage );
		void DrawAnimation( int iID, Maths::Vector<2> v2Position, float fDepth, float fRunTime );
		void DrawAnimationFrame( int ID, Maths::Vector<2> v2Position, float fDepth, int iFrame );
		void UnloadAll();
		void Destroy();
		void SetCameraPosition( Maths::Vector<2> v2Position );
		Maths::Vector<2> GetCameraPosition();

	private:
		HTEXTURE LoadTexture( const char* Filename );

	private:
		//Haaf instance
		HGE* m_pHGE;
		hgeFont* m_pFont;
		int m_iSpriteIndex;
		int m_iAnimationIndex;
		SpriteVector m_SpriteVector;
		AnimationVector m_AnimationVector;
		TextureVector m_Textures;
		char m_RootDir[s_iStringLength];
		Maths::Vector<2> m_v2CameraPosition;
	};
}



#endif//_HGE_RENDERER_H_