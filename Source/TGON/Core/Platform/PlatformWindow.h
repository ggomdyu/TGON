/*
* Author : Cha Junho
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsWindowFrame.h"
#endif

namespace tgon
{

template <typename WindowTy, 
		  typename = typename std::enable_if<std::is_convertible<WindowTy*, TWindowFrame*>::value>::type>
std::shared_ptr<TWindowFrame> MakeWindow( 
	const WindowStyle& wndStyle )
{
	return std::make_shared<WindowTy>( wndStyle );
}

}