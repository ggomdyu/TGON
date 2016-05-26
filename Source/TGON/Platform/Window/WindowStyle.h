/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include <stdint.h>
#include <string>
#include "../../Platform/Slate/PlatformFwd.h"

namespace tgon
{


struct WindowStyle
{
public:
	WindowStyle() {}

	static WindowStyle ParseFromXML( const wchar_t* const xmlPath );

public:
	std::wstring caption = L"TGON-Default";

	/* Shape */
	int32_t x = 100;
	int32_t y = 100;
	int32_t width = 500;
	int32_t height = 500;

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
};



}

