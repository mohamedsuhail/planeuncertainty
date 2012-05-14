#ifndef ENTITY_H_
#define ENTITY_H_

#include "Components/Component.h"
#include <list>

class Entity
{
public:
	void AddComponent( Component* pComponent );
};

#endif//ENTITY_H_