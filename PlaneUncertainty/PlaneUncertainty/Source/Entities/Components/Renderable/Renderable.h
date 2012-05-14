#ifndef RENDERABLE_H_
#define RENDERABLE_H_
#include "Entities/Components/Component.h"

class Renderable : Component
{
public:
	virtual bool Init( Entity* Parent );
	virtual eType GetType();
	virtual bool Valid();

};

#endif//RENDERABLE_H_