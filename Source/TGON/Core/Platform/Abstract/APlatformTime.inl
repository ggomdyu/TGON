/*
 * Author : Cha Junho
 * Date : 05/15/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "APlatformTime.h"

#include <boost/config/suffix.hpp>


namespace tgon
{


template <class DerivedTy>
const uint32_t APlatformTime<DerivedTy>::ms_oldTime = DerivedTy::GetBootTime( );


template<typename DerivedTy>
BOOST_FORCEINLINE uint32_t APlatformTime<DerivedTy>::GetAppExecutionTime( )
{
	return DerivedTy::GetBootTime( ) - ms_oldTime;
}


} /*namespace tgon*/