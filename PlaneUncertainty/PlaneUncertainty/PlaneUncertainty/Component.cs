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
            Parent.AddComponent( this );
        }

        public virtual eType Type
        {
            get
            {
                return eType.INVALID;
            }
        }

        public virtual bool Valid()
        {
            return m_bInitialised && Type != eType.INVALID;
        }


        protected Entity m_Parent = null;
        protected bool m_bInitialised = false;
    }
}
