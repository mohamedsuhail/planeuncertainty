using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PlaneUncertainty
{
    class Animation : Renderable
    {
        public override void Init( Entity Parent )
        {
            base.Init( Parent );
            m_eType = eType.Animation;
        }
        public Animation()
        {
            m_eType = eType.Animation;
        }
        public void bollocks()
        {

        }
        int m_iNumFrames = -1;
        float m_fDuration = -1f;
    }
}
