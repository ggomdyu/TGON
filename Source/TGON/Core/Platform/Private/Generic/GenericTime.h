/**
 * filename GenericTime.h
 * author   ggomdyu
 * since    05/15/2016
 */

#pragma once
#include "../..//TConfig.h"

#include <cstdint>

namespace tgon
{

enum class DayOfWeek
{
	Sunday = 0,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
};

struct LocalTime
{
	int32_t month;
	int32_t day;
	int32_t year;
	int32_t hour;
	int32_t minute;
	int32_t second;
	DayOfWeek dayOfWeek;
};

template <typename PlatformTimeTy>
class TGON_API GenericTime
{
/**
 * @section Public command methods
 */
public:
	/**
	 * @brief               Put to sleep which caller thread of this function while passed millisecond
	 * @param   milliSec    Caller thread's sleep time
	 */
	static void Sleep(unsigned int milliSec);

/**
 * @section Get methods
 */
public:
    /*@return  Start time of process as millisecond*/
    static std::size_t GetAppStartTime();
        	
	/*@return  Execution time of process as millisecond*/
	static std::size_t GetAppExecutionTime();

/**
 * @section Private variables
 */
private:
	static const std::size_t ms_oldTime;

/**
 * @section Ctor/Dtor
 */
public:
	GenericTime() = delete;
	~GenericTime() = delete;
};

template <class PlatformTimeTy>
const std::size_t GenericTime<PlatformTimeTy>::ms_oldTime = PlatformTimeTy::GetBootTime();

template<typename PlatformTimeTy>
inline std::size_t GenericTime<PlatformTimeTy>::GetAppExecutionTime()
{
	return PlatformTimeTy::GetBootTime() - ms_oldTime;
}

} /* namespace tgon */
