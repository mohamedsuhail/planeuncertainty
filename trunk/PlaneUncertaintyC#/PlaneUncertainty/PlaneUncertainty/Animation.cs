using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using System.Diagnostics;

namespace PlaneUncertainty
{
    class Animation : Renderable
    {
        public override void Init( Entity Parent )
        {
            base.Init( Parent );
        }

        public override void Draw( Microsoft.Xna.Framework.Graphics.SpriteBatch Renderer )
        {
            

        }

        public void LoadTexture( string Name, ContentManager Loader, int iNumFrames )
        {
            base.LoadTexture( Name, Loader );

            int[] iDimensions = new int[2];
            iDimensions[0] = m_Texture.Width;
            iDimensions[1] = m_Texture.Height;
            
            int iFrameSize = iDimensions[0] > iDimensions[1] ? iDimensions[1] : iDimensions[0];
            int iTotalSize = iDimensions[0] * iDimensions[1];
            bool bFound = Convert.ToBoolean( iTotalSize / ( iFrameSize * iFrameSize) == iNumFrames);

            while ( !bFound )
            {
                iFrameSize /= 2;
                bFound = Convert.ToBoolean( iTotalSize / ( iFrameSize * iFrameSize ) == iNumFrames );
            }
            m_iFrameSize = iFrameSize;
        }

        public float FRAME_DURATION
        {
            get
            {
                return 0.25f;
            }
        }

        public void Play( int iFrameStart, int iFrameEnd, bool bLooping = true )
        {
            m_iFrameStartEnd[0] = iFrameStart;
            m_iFrameStartEnd[1] = iFrameEnd;
            m_bLoop = bLooping;
        }

        public override Component.eType Type
        {
            get
            {
                return eType.Animation;
            }
        }


        protected int m_iFrameSize = -1;
        protected int m_iNumFrames = -1;
        protected float m_fStartTime = -1f;
        protected bool m_bLoop = false;
        protected int[] m_iFrameStartEnd = new int[2];
    }
}
