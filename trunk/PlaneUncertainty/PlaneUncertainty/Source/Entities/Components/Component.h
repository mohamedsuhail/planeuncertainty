#ifndef COMPONENT_H_
#define COMPONENT_H_

class Entity;

class Component
{
public:
	enum eType 
	{
		CMP_INVALID = -1,
		CMP_FIRST = 0,

		CMP_Renderable = CMP_FIRST,

		COUNT
	};

	virtual bool Init( Entity* Parent );
	virtual eType GetType();
	virtual bool Valid();

protected:
	Entity* m_Parent;
	bool m_bInitialised;
};
#endif//COMPONENT_H_