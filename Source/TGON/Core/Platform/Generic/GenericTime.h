/*
 * Author : Cha Junho
 * Date : 05/15/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <cstdint>
#include <boost/config/suffix.hpp>


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

template <typename DerivedTy>
class TGON_API GenericTime
{
	/*
	 * Ctor/Dtor
	*/
public:
	GenericTime( ) = delete;
	~GenericTime( ) = delete;

	/*
	 * Commands
	*/
public:
	/* @return Return this process's execution time as millisecond */
	static uint32_t GetAppExecutionTime( );

	/*
	* Variables
	*/
private:
	static const uint32_t ms_oldTime;
};


template <class DerivedTy>
const uint32_t GenericTime<DerivedTy>::ms_oldTime = DerivedTy::GetBootTime( );


template<typename DerivedTy>
BOOST_FORCEINLINE uint32_t GenericTime<DerivedTy>::GetAppExecutionTime( )
{
	return DerivedTy::GetBootTime( ) - ms_oldTime;
}


} /*namespace tgon*/
