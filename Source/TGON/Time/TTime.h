#pragma once
#include <chrono>


namespace tgon
{


class TTime
{
private:
	typedef std::chrono::time_point<std::chrono::system_clock,
		std::chrono::milliseconds> ms_time_point;
	typedef std::chrono::time_point<std::chrono::system_clock,
		std::chrono::minutes> m_time_point;
	typedef std::chrono::time_point<std::chrono::system_clock,
		std::chrono::seconds> s_time_point;

	TTime( ) {};
	~TTime( ) {};

public:
	// Singleton
	static TTime* Get( )
	{
		static TTime timeInst;
		return &timeInst;
	}

	int64_t GetExecutionTime( ) const;
	float	GetElapsedTime( );

private:
	static const s_time_point ms_bootStartTime;
};


}