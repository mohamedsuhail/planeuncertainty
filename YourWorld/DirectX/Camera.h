#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3dx9.h>

class Camera
{
public:
	void Reset();
	D3DXMATRIX BuildViewMatrix();

private:
	D3DXVECTOR3 m_Position, m_Up, m_Look, m_Right ;
	float m_Yaw, m_Pitch, m_Roll;
};
#endif