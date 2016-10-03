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
	//
	// Gets
	//
public:
	/*
	* @note	Toggle the full-screen.
	* @return	Return true on success.
	*/
	static bool ToggleFullScreen( const class GenericWindowFrame& window ) {}

	/* @note	Get monitor's count. */
	static int32_t GetMonitorCount( ) { return 0; }

	/* @note	Get main monitor's screen width. */
	static int32_t GetMainWidth( ) { return 0; }

	/* @note	Get main monitor's screen height. */
	static int32_t GetMainHeight( ) { return 0; }
	
	// 
	// Ctor/Dtor
	// 
public:
	GenericScreen( ) = delete;
	~GenericScreen( ) = delete;

};


}