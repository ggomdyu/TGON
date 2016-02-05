/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : ����ȣ
* ���� ������ : 2016-01-09
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