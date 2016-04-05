/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <string>
#include "../Config/Platform/PlatformFwd.h"
#include <stdint.h>


namespace tgon {
	

struct WindowStyle
{
public:
	WindowStyle() {}

	static WindowStyle ParseFromXML( const wchar_t* const xmlPath );

public:
	std::wstring caption = L"Default-Caption";

	/* Shape */
	uint32_t x = 100;
	uint32_t y = 100;
	uint32_t width = 500;
	uint32_t height = 500;

	bool Popup = false;
	bool Maximized = false;
	bool Minimized = false;

	/* Funtional */
	bool SupportWindowTransparency = false;
	bool SupportPerPixelTransparency = false;
	bool ShowTopOnCreated = false;
	bool Resizeable = true;
	bool TopMost = false;
	bool ShowMiddle = true;
	bool ShowImmediately = true;
	
	/* Callback */
	int32_t( *msgCallback )( class TWindow*, enum struct WindowEvent ) = nullptr;
};



}

