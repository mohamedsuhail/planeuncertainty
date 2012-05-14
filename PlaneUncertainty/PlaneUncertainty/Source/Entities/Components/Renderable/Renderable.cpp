#include "Renderable.h"

bool Renderable::Init( Entity* Parent )
{
	Component::Init( Parent );

	return true;
}

Component::eType Renderable::GetType()
{
	return CMP_Renderable;
}

bool Renderable::Valid()
{
	if( Component::Valid() )
	{
		return true;
	}
}