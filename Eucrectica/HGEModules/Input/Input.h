#ifndef INPUT_H_
#define INPUT_H_

#include "../Types_And_Defines/InputTypes.h"

class HGE;

namespace HGE_Modules
{
	class Input
	{
		struct InputKey
		{
			InputTypes::eAction m_eAction;
			int m_iHGEKeyMap;
			InputKey( InputTypes::eAction eAction, int iHGEKeyMap ): m_eAction(eAction),m_iHGEKeyMap(iHGEKeyMap)
			{

			}
			InputKey(): m_eAction(InputTypes::Invalid), m_iHGEKeyMap(-1)
			{

			}
		};

		typedef asl::static_vector<InputKey, InputTypes::NumberOf * 2> InputKeyVector;
	public:
		Input();
		void Init( HGE* pHGE );
		bool Update(); //returns true if exit command is pressed
		InputTypes::FrameInput GetFrameInput();
	private:
		HGE* m_pHGE;
		InputKeyVector m_InputKeyVector;
		InputTypes::FrameInput m_FrameInput;
	};

}
#endif//INPUT_H_