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
    class Renderable : Component
    {
        public override void Init( Entity Parent )
        {
            base.Init( Parent );
            s_RenderList.Add( this );
        }

        public void Destroy()
        {
            s_RenderList.Remove( this );
            //TODO: remove it from the content manager that was holding it
        }

        public virtual void Draw( SpriteBatch Renderer )
        {
            Renderer.Draw( m_Texture, m_vPosition, Color.White );
        }

        public void LoadTexture( string Name, ContentManager Loader )
        {
            Debug.Assert( m_Texture == null );
            m_Texture = Loader.Load<Texture2D>( Name );
        }

        public static void DrawAll( SpriteBatch Renderer )
        {
            foreach ( Renderable Iter in s_RenderList )
            {
                Iter.Draw( Renderer );
            }
        }

        public override Component.eType Type
        {
            get
            {
                return eType.Renderable;
            }
        }

        protected static List<Renderable> s_RenderList = new List<Renderable>();
        protected static float m_fFrameTime = 0f;
        protected Vector2 m_vPosition = Vector2.Zero;
        protected Texture2D m_Texture = null;
    }
}
