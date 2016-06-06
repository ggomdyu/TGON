/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Slate/PlatformFwd.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


struct TGON_API WindowStyle
{
public:
	WindowStyle() {}
	static WindowStyle LoadFromXML( const wchar_t* xmlPath );

public:
	std::wstring title = L"TGON-Default";

	/*
		Transform
	*/
	int32_t x = 100;
	int32_t y = 100;
	int32_t width = 500;
	int32_t height = 500;

	/*
		Style
	*/
	bool Popup = false;

	/*
		Function
	*/
	bool ClipCursor = false;
	bool FullScreen = false;
	bool EventHandleable = true;
	bool SupportWindowTransparency = false;
	bool SupportPerPixelTransparency = false;
	bool ShowTopOnCreated = false;
	bool Resizeable = true;
	bool TopMost = false;
	bool Maximized = false;
	bool Minimized = false;
	bool ShowMiddle = true;
	bool ShowImmediately = true;
};



}

