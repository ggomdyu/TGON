/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-08-29
* ���� ���� : ����ȣ
* ���� ������ : 2015-12-14
*/
#pragma once
#include "ISystem.h"
#include <Pattern\Singleton.h>

#include <chrono>

namespace tgon {
	class TickSystem final : public ISystem
	{
		typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> MinTimePoint;
		typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> SecTimePoint;
		typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> MiliTimePoint;

	public:
		Declare_Static_Singleton( TickSystem )

	public:
		virtual void FrameMove( float elapsedTime ) override;
		virtual void RecvMessage( _In_ const SociableMessage& msg ) override;

	public:
		float GetElapsedTime( ) const { return m_elapsedTime; }

	private:
		TickSystem( );
		~TickSystem( );

	private:
		MiliTimePoint m_startTime;
		float m_elapsedTime;
	};
}