#include "Camera.h"

void Camera::Reset()
{
	m_Up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_Look=D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_Right=D3DXVECTOR3(1.0f,0.0f,0.0f);
}

D3DXMATRIX Camera::BuildViewMatrix()
{
	Reset();

	D3DXMATRIX yawMat;
	D3DXMatrixRotationAxis(&yawMat, &m_Up, D3DXToRadian(m_Yaw));
	D3DXVec3TransformCoord(&m_Look, &m_Look, &yawMat);
	D3DXVec3TransformCoord(&m_Right,&m_Right,&yawMat);

	D3DXMATRIX pitchMat;
	D3DXMatrixRotationAxis(&pitchMat, &m_Right,D3DXToRadian(m_Pitch));
	D3DXVec3TransformCoord(&m_Look, &m_Look, &pitchMat);
	D3DXVec3TransformCoord(&m_Up, &m_Up, &pitchMat);

	D3DXMATRIX rollMat;
	D3DXMatrixRotationAxis(&rollMat, &m_Look, D3DXToRadian(m_Roll));
	D3DXVec3TransformCoord(&m_Right, &m_Right, &rollMat);
	D3DXVec3TransformCoord(&m_Up, &m_Up, &rollMat);

	D3DXMATRIX View;
	D3DXMatrixIdentity(&View);

	View._11 = m_Right.x; 
	View._12 = m_Up.x; 
	View._13 = m_Look.x;
	View._21 = m_Right.y; 
	View._22 = m_Up.y;
	View._23 = m_Look.y;
	View._31 = m_Right.z; 
	View._32 = m_Up.z; 
	View._33 = m_Look.z;

	View._41 = - D3DXVec3Dot( &m_Position, &m_Right );
	View._42 = - D3DXVec3Dot( &m_Position, &m_Up );
	View._43 = - D3DXVec3Dot( &m_Position, &m_Look );
	return View;
}