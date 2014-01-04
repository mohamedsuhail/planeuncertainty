#include "Animation.h"
#include "../Haaf/include/hgesprite.h"

namespace HGE_Modules
{

	Animation::Animation( )
		: m_iFrameWidth( 0 )
		, m_iFrameHeight( 0 )
		, m_Texture( 0 )
		, m_bRepeating( true )
		, m_iNumFramesWide( 0 )
		, m_iNumFramesHigh( 0 )
		, m_iDuration( 0.f )
	{

	}

	void Animation::Clear()
	{
		delete m_pSprite;
	}

	void Animation::Construct( HGE* pHGE, int iFrameWidth, int iFrameHeight
		, HTEXTURE Texture, int iDuration, bool bRepeating /* = true */ )
	{
		m_iFrameWidth = iFrameWidth;
		m_iFrameHeight = iFrameHeight;
		m_Texture = Texture;
		m_iDuration = iDuration;
		m_bRepeating = bRepeating;
		m_iNumFramesWide = pHGE->Texture_GetWidth(Texture) /  m_iFrameWidth;
		m_iNumFramesHigh = pHGE->Texture_GetHeight(Texture) / iFrameHeight;
		m_iFrameDuration = m_iDuration / ( m_iNumFramesWide * m_iNumFramesHigh );

		m_pSprite = new hgeSprite( Texture, 0, 0, iFrameWidth, iFrameHeight );
	}

	Maths::Vector<2> Animation::GetFrameRectangle( float fTimeInMilliseconds )
	{
		int iTimeInMilliseconds( fTimeInMilliseconds * 1000 );
		//if the animation has run for its duration and doesn't repeat
		if( iTimeInMilliseconds > m_iDuration && !m_bRepeating )
		{
			//return the final frame
			return Maths::Vector<2>( m_iFrameWidth * (m_iNumFramesWide) - 1, m_iFrameHeight * ( m_iNumFramesHigh - 1) );
		}

		//get the time that will actually count for this frame
		int iFrameTime( iTimeInMilliseconds % m_iDuration );
		//calculate the current frame
		int iFrame( iFrameTime / m_iFrameDuration );

		return Maths::Vector<2>( m_iFrameWidth * ( iFrame % m_iNumFramesWide), m_iFrameHeight * ( iFrame / m_iNumFramesWide ) );

	}

	void Animation::Render( float fTimeInMilliseconds, Maths::Vector<2> v2Position, float fDepth )
	{
		Maths::Vector<2> v2Frame( GetFrameRectangle(fTimeInMilliseconds) );
		m_pSprite->SetTextureRect( v2Frame[0], v2Frame[1], m_iFrameWidth, m_iFrameHeight );
		m_pSprite->SetZ( fDepth );
		m_pSprite->Render( v2Position[0], v2Position[1] );
	}

	void Animation::Render( int iFrame, Maths::Vector<2> v2Position, float fDepth )
	{
		Maths::Vector<2> v2Frame( m_iFrameWidth * ( iFrame % m_iNumFramesWide), m_iFrameHeight * ( iFrame / m_iNumFramesWide ) );
		m_pSprite->SetTextureRect( v2Frame[0], v2Frame[1], m_iFrameWidth, m_iFrameHeight );
		m_pSprite->SetZ( fDepth );
		m_pSprite->Render( v2Position[0], v2Position[1] );
	}

}