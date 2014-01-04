#pragma once
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../Haaf/include/hge.h"

class hgeSprite;

namespace HGE_Modules
{
	class Animation
	{
	public:
		Animation( );
		void Construct(	  HGE* pHGE
			, int iFrameWidth
			, int iFrameHeight
			, HTEXTURE Texture
			, int iDuration
			, bool bRepeating = true );
		void Clear();

		void Render( float fTimeInMilliseconds, Maths::Vector<2> v2Position, float fDepth );
		void Render( int iFrame, Maths::Vector<2> v2Position, float fDepth );

	private:
		Maths::Vector<2> GetFrameRectangle( float fTimeInMilliseconds );

	private:
		HTEXTURE m_Texture;
		int m_iFrameWidth;
		int m_iFrameHeight;
		int m_iDuration;
		bool m_bRepeating;
		int m_iNumFramesWide;
		int m_iNumFramesHigh;
		int m_iFrameDuration;
		hgeSprite* m_pSprite;
	};
}


#endif//ANIMATION_H_