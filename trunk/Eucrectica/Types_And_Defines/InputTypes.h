#ifndef _INPUTTYPES_H_
#define _INPUTTYPES_H_
#include "Vector.h"
namespace InputTypes
{
	enum eAction
	{
		Invalid = -1,
		First = 0,
		MoveUp = First,
		MoveDown,
		MoveLeft,
		MoveRight,
		LeftClick,
		RightClick,
		Escape,
		AlternateAction,
// 		Action1,
// 		Action2,
// 		Action3,
// 		Action4,
		Hotbar1,
		Hotbar2,
		Hotbar3,
		Hotbar4,
		Hotbar5,
		Hotbar6,
		Hotbar7,
		Hotbar8,
		Hotbar9,
		Hotbar0,
		NumberOf
	};

	
	struct FrameInput
	{
		bool Actions[NumberOf];
		Maths::Vector<2> MousePosition;
		void Clear()
		{
			for( int i = 0; i < NumberOf; ++i )
			{
				Actions[i] = false;
			}
			MousePosition = Maths::Vector<2>(0,0);
		}
	};
}


#endif //_INPUTTYPES_H_