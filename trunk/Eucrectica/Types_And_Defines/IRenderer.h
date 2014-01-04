#ifndef IRENDERER_H_
#define IRENDERER_H_

struct IRenderer
{
	virtual int LoadSprite( const char* FileName, Maths::Vector<2> v2FrameDimensions ) = 0;
	virtual int LoadAnimation( const char* FileName, Maths::Vector<2> v2FrameDimensions, int iDuration, bool bRepeating = true ) = 0;
	virtual void LoadFont( const char* FileName ) = 0;
	virtual void DrawSprite( int iID, Maths::Vector<2> v2Position, float fDepth ) = 0;
	virtual void DrawSpritePartial( int iID, Maths::Vector<2> v2Position, float fDepth, float fWidthPercentage, float fHeightPercentage ) = 0;
	virtual void DrawAnimation( int iID, Maths::Vector<2> v2Position, float fDepth, float fRunTime ) = 0;
	virtual void DrawAnimationFrame( int ID, Maths::Vector<2> v2Position, float fDepth, int iFrame ) = 0;
	virtual void SetCameraPosition( Maths::Vector<2> v2Position ) = 0;
	virtual Maths::Vector<2> GetCameraPosition() = 0;
};
#endif//IRENDERER_H_