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
	static WindowStyle LoadFromXML( /*IN*/ const char* xmlPath );
	static const WindowStyle ms_defaultStyle;

public:
	/*
		Title
	*/
	// UTF-8 encoded window title
	std::string title = u8"TGON-Default";


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
		Style
	*/
	// If border is Useless, switch this to true.
	bool Popup = false;


	/*
		Function
	*/
	// Clip the cursor on window or not.
	bool ClipCursor = false;

	//
	bool FullScreen = false;
	
	// EventHandleable means allow event handler calling( e.g. OnLMouseDown, OnSized, ... )
	// @ WARNING! : OnIdle is not affected by this flag.
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

