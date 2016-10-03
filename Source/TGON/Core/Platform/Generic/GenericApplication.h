/*
 * Author : Cha Junho
 * Date : 03/20/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../PlatformInclude.h"

#include <cstdint>


namespace tgon 
{


template <typename DerivedTy>
class TGON_API GenericApplication
{
	// 
	// Commands
	// 
public:
	/*
	 * @note Update all of message queue.
	 * @return Return false if there is no event to pump out
	*/
	static bool PumpEvent( ) {}

	/*
	 * @note Exit thread by force. This function is not recommended.
	 * @param exitCode Pass exit code.
	*/
	static void ExitThread( int32_t exitCode ) {}

	/*
	 * @note Quit application with passing exit code.
	 * @param exitCode Pass exit code.
	*/
	static void Quit( int32_t exitCode ) {}

	/*
	 * @note Enable show cursor mode: Hide or Show
	 * @param enableShow True is show, false is hide.
	*/
	static void ShowCursor( bool enableShow ) {}

	// 
	// Ctor/Dtor
	// 
public:
	GenericApplication( ) = delete;
	~GenericApplication( ) = delete;

};


} /*namespace tgon*/
