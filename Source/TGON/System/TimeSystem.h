/*
* Author : Junho-Cha
* Date : 05/10/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include "../Core/TObject.h"
#include "../Core/TSingleton.h"
#include "../Platform/Time/TTime.h"
#include "../System/ISystem.h"


namespace tgon
{


class TimeSystem : public ISystem
{
public:
	TGON_OBJECT( TimeSystem, TObject )
	TGON_SINGLETON( TimeSystem )

	virtual void Update( float tickTIme ) override;

public:
	// Get or return 0.0 ~ 1.0
	void SetTimeScale( float timeScale );
	float GetTimeScale( ) const;
	float GetTickTime( ) const;

protected:
	TimeSystem( );
	virtual ~TimeSystem( );

private:
	uint32_t m_oldTime;
	uint32_t m_tickTime;
	float m_timeScale;
};


inline void tgon::TimeSystem::SetTimeScale( float timeScale )
{
	// TODO : Change to message system...
	m_timeScale = timeScale;
}

inline float tgon::TimeSystem::GetTimeScale( ) const
{
	return m_timeScale;
}

inline float tgon::TimeSystem::GetTickTime( ) const
{
	return m_tickTime * 0.001f * m_timeScale;
}


}