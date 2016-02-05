/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-09
*/

#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "..\..\TGON_Windows.Core\Sources\WindowsWindow.h"
#else
#endif
#include <memory>


namespace tgon {
namespace Window {


typedef WindowImpl						TWindow;

/* Smart pointer type */
typedef std::shared_ptr<TWindow>	SpTWindow;


}
}