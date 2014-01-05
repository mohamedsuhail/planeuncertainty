#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>

class Camera
{
public:
	void Reset();

private:
	D3DXVECTOR3 m_Position;
};
#endif