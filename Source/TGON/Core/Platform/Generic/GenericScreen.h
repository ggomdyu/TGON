/*
* Author : Cha Junho
* Date : 07/05/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/PlatformInclude.h"

#include <cstdint>


namespace tgon
{


template <typename DerivedTy>
class TGON_API GenericScreen
{
public:
	// 
	// Gets
	// 
	/* @note	Get monitor's count. */
	static int32_t GetMonitorCount( );

	/* @note	Get main monitor's screen width. */
	static int32_t GetMainWidth( );

	/* @note	Get main monitor's screen height. */
	static int32_t GetMainHeight( );
	
public:
	// 
	// Ctor/Dtor
	// 
	GenericScreen( ) = delete;
	~GenericScreen( ) = delete;

};


template <typename DerivedTy>
inline int32_t GenericScreen<DerivedTy>::GetMonitorCount( )
{
	return 0;
}

template <typename DerivedTy>
inline int32_t GenericScreen<DerivedTy>::GetMainWidth( )
{
	return 0;
}

template <typename DerivedTy>
inline int32_t GenericScreen<DerivedTy>::GetMainHeight( )
{
	return 0;
}

}