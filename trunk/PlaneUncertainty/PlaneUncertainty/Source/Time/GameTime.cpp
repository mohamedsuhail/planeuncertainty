#include "GameTime.h"
#include <Windows.h>

namespace GameTime
{
	static float m_fFrequency( 0.f );
	static unsigned int m_uiStartTime;
	static unsigned int m_uiEndTime;
	static unsigned int m_uiLastTime;
	static float m_fTime = ( 0.f );
	static float m_fDT = ( 0.f );

	void Update()
	{
		static bool bFirstTime( true );

		if( bFirstTime )
		{
			unsigned __int64 freq;
			QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
			m_fFrequency = (1.0/freq);

			QueryPerformanceCounter((LARGE_INTEGER *)&m_uiStartTime);
			bFirstTime = false;
		}

		QueryPerformanceCounter((LARGE_INTEGER *)&m_uiEndTime);
		m_fDT = ((m_uiEndTime-m_uiLastTime) * m_fFrequency);
		m_uiLastTime = m_uiEndTime;

		m_fTime = ((m_uiEndTime-m_uiStartTime) * m_fFrequency);
	}

	float GetTimeMs()
	{
		return m_fTime;
	}

	float GetDTMs()
	{
		return m_fDT;
	}
}