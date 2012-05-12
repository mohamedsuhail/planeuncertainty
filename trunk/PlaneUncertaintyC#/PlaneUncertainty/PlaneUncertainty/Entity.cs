using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace PlaneUncertainty
{
    class Entity
    {
        public void AddComponent( Component Child )
        {
            m_Components.Add( Child.Type, Child );
        }

        
        protected Dictionary<Component.eType, Component> m_Components = new Dictionary<Component.eType, Component>();

    }
}
