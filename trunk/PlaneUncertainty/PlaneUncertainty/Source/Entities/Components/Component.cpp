#include "Component.h"
#include "Entities/Entity.h"
bool Component::Init( Entity* Parent )
{
	m_Parent = Parent;
	m_bInitialised = true;

	return true;
}

bool Component::Valid()
{
	return m_bInitialised && GetType() != CMP_INVALID;
}