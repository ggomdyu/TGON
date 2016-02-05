/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#if	!defined( PLATFORM_WINDOWS_OS ) &&		\
		!defined( PLATFORM_ANDROID_OS )
{
	#error	 "Your platform is not supported."
}
#endif

#include <System\ISystem.h>
#include <Pattern\Singleton.h>

#include <vector>
#include "TWindow.h"
#include <initializer_list>


namespace tgon {
namespace CoreEngine {


	void Setup( const Window::SpTWindow& pWnd );
	void Setup( const Window::SpTWindow& pWnd, const std::initializer_list<ISystem*>& );

	const tgon::Window::SpTWindow& GetWindow( );
	
	/*
		- Window event dispatching?

		Process all of window that has message queue.
		If there are no message to pull, return WindowEvent::None.
	*/
	void DispatchEvent( _Out_ tgon::Window::WindowEvent* outGlobalEvent );
	void Run( );


	}
}