using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace PlaneUncertainty
{
    abstract class Component
    {
        public enum eType
        {
            INVALID = -1,

            First = 0,

            Renderable = First,
            Animation,

            Count
        }

        public virtual void Init( Entity Parent)
        {
            Debug.Assert( !m_bInitialised );
            m_Parent = Parent;
            m_bInitialised = true;
            m_P
        }

        public eType Type
        {
            get
            {
                Debug.Assert( m_eType != eType.INVALID );
                return m_eType;
            }
        }

        public virtual bool Valid()
        {
            return m_bInitialised && m_eType != eType.INVALID;
        }

        protected Entity m_Parent = null;
        protected eType m_eType = eType.INVALID;
        protected bool m_bInitialised = false;
    }
}
