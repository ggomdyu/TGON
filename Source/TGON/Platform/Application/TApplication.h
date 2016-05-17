/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include "../Platform/Slate/PlatformApplication.h"
#include "../Platform/Config/Build.h"
#include "../Config/SyntaxCompatible.h"


namespace tgon
{


class TGON_API TApplication : 
	public ApplicationImpl
{
public:
	static bool DispatchEvent( _Out_ enum struct WindowEvent* );

	static void GetScreenSize( int32_t* width, int32_t* height );

	static TSystemBatteryInfo GetPowerInfo( );


private:
	TApplication( ) = delete;
	~TApplication( ) = delete;
};


BOOST_FORCEINLINE bool TApplication::DispatchEvent( _Out_ WindowEvent* wndEvent )
{
	return ApplicationImpl::DispatchEvent( wndEvent );
}

BOOST_FORCEINLINE void TApplication::GetScreenSize( int32_t* width, int32_t* height )
{
	ApplicationImpl::GetScreenSize( width, height );
}

BOOST_FORCEINLINE TSystemBatteryInfo TApplication::GetPowerInfo( )
{
	return ApplicationImpl::GetPowerInfo( );
}


}