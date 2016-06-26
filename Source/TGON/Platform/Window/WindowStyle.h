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
	static WindowStyle LoadFromXML( const wchar_t* xmlPath );

public:
	std::wstring title = L"TGON-Default";


	/*
		Transform
	*/
	// Window's position
	int32_t x = 100;
	int32_t y = 100;
	
	// Window's scale
	int32_t width = 500;
	int32_t height = 500;


	/*
		Show style
	*/
	// If border is Useless, switch this to true.
	bool Popup = false;


	/*
		Function
	*/
	bool FullScreen = false;
	bool EventHandleable = true;
	
	// Enable window surface's transparency or not.
	bool SupportWindowTransparency = false;
	
	// Enable window surface's per-pixel transparency or not.
	bool SupportPerPixelTransparency = false;
	
	bool ShowTopOnCreated = false;
	
	bool Resizeable = true;
	bool TopMost = false;
	bool Maximized = false;
	bool Minimized = false;
	
	// 
	bool ShowMiddle = true;
	
	//
	bool ShowImmediately = true;

public:
	WindowStyle( );
	~WindowStyle( );
};



}

