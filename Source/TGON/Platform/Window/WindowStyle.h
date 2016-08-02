/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include <string>


namespace tgon
{


struct WindowStyle
{
public:
	/*
		Public member
	*/
	static const WindowStyle DefaultStyle;


public:
	/*
		Commands
	*/
	static WindowStyle LoadFromXML( const char* xmlPath );


public:
	std::string title = "TGON-Default";

	// Window's transform
	int32_t x = 100;
	int32_t y = 100;
	int32_t width = 500;
	int32_t height = 500;

	// If border is useless, switch this to true.
	bool popup = false;

	// Show window as full-screen when it was created.
	bool fullScreen = false;

	// Enable window surface's transparency.
	bool supportWindowTransparency = false;
	
	// Enable window surface's per-pixel transparency.
	bool supportPerPixelTransparency = false;
	
	// 
	bool showTopOnCreated = false;

	// Enable window's resizing. 
	bool resizeable = true;
	
	// Show window always top.
	// @ WARNING : It can cause race each other top-most window
	bool topMost = false;

	// Set window maximized when it was created.
	bool maximized = false;
	
	// Set window minimized when it was created.
	bool minimized = false;
	
	// Set window's position to middle when it was created.
	bool showMiddle = true;
	
	//
	bool showImmediately = true;


public:
	/*
		Cons/Destructor
	*/
	WindowStyle( ) = default;

	~WindowStyle( ) = default;
};


}