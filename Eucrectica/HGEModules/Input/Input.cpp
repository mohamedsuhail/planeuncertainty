#include "Input.h"
#include "../Haaf/include/hge.h"

namespace HGE_Modules
{
	Input::Input(): m_pHGE(NULL)
	{

	}

	void Input::Init( HGE* pHGE )
	{
		//To Do: Read/Store keys from file	
		m_pHGE = pHGE;

		m_InputKeyVector.push_back( InputKey( InputTypes::LeftClick, HGEK_LBUTTON ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::RightClick, HGEK_RBUTTON ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveLeft, HGEK_A ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveLeft, HGEK_LEFT ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveRight, HGEK_D ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveRight, HGEK_RIGHT ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveUp, HGEK_W ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveUp, HGEK_UP ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveDown, HGEK_S ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::MoveDown, HGEK_DOWN ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Escape, HGEK_ESCAPE ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::AlternateAction, HGEK_SHIFT ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar0, HGEK_0 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar1, HGEK_1 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar2, HGEK_2 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar3, HGEK_3 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar4, HGEK_4 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar5, HGEK_5 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar6, HGEK_6 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar7, HGEK_7 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar8, HGEK_8 ) );
		m_InputKeyVector.push_back( InputKey( InputTypes::Hotbar9, HGEK_9 ) );


	
	}

	bool Input::Update()
	{
		//check for exit
		if ( m_pHGE->Input_GetKeyState( HGEK_ESCAPE ) ) 
		{
			return true;
		}

		m_FrameInput.Clear();

		for( InputKeyVector::iterator iter( m_InputKeyVector.begin() ), endIter( m_InputKeyVector.end());
			 iter != endIter;
			 ++iter )
		{
			if( m_pHGE->Input_GetKeyState( (*iter).m_iHGEKeyMap) )
			{
				m_FrameInput.Actions[(*iter).m_eAction] = true;
			}
		}

		m_pHGE->Input_GetMousePos( &m_FrameInput.MousePosition[0], &m_FrameInput.MousePosition[1] );


		return false;
	}
}
