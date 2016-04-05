#include "PrecompiledHeader.h"
#include "TTime.h"

#include "../Config/Compiler/SyntaxCompatible.hpp"


using namespace std;
using namespace std::chrono;

using std::chrono::time_point;
using std::chrono::time_point_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


const tgon::TTime::s_time_point tgon::TTime::ms_bootStartTime(
		time_point_cast<seconds>(
				system_clock::now( )
			));



int64_t tgon::TTime::GetExecutionTime( ) const
{
	const s_time_point curTime = time_point_cast<seconds>(
			system_clock::now( ));

	return ( curTime-ms_bootStartTime ).count();
}


float tgon::TTime::GetElapsedTime( )
{
	TGON_THREAD_LOCAL auto startTime(
			time_point_cast<milliseconds>( system_clock::now( )));
	const auto endTime(
			time_point_cast<milliseconds>( system_clock::now( )));

	const float elapsedTime = static_cast<float>((
			endTime-startTime ).count( ))*0.001f;
	startTime = endTime;

	return elapsedTime;
}