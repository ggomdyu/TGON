/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


struct WindowStyle
{
public:
	static WindowStyle LoadFromXML( const char* xmlPath );
	
	static WindowStyle DefaultStyle;


public:
	/*
		Caption
	*/
	std::string title = "TGON-Default";

	
	/*
		Transform
	*/
	// Window's position
	// @ Platform : Windows
	int32_t x = 100;
	int32_t y = 100;
	
	// Window's scale
	// @ Platform : Windows
	int32_t width = 500;
	int32_t height = 500;


	/*
		Show style
	*/
	// If border is Useless, switch this to true.
	// @ Platform : Windows
	bool Popup = false;


	/*
		Function
	*/
	// Show window as full-screen when created
	// @ Platform : Windows
	bool FullScreen = false;

	// @ WARNING : <OnIdle> event handler is not applied to the description below.
	// --- What is the 'EventHandleable'?
	// If you pass false to this, You can make more fast window 
	// but which cannot handle event( e.g. OnMouseMove, OnDestroying, etc... )
	// @ Platform : Windows
	bool EventHandleable = true;
	
	// Enable window surface's transparency or not.
	// @ Platform : Windows
	bool SupportWindowTransparency = false;
	
	// Enable window surface's per-pixel transparency or not.
	// @ Platform : Windows
	bool SupportPerPixelTransparency = false;
	
	// 
	// @ Platform : Windows
	bool ShowTopOnCreated = false;

	// Enable resize frame 
	// @ Platform : Windows
	bool Resizeable = true;
	
	// Show window always top.
	// @ WARNING : It can cause race each other top-most window
	// @ Platform : Windows
	bool TopMost = false;

	//
	bool Maximized = false;
	
	//
	bool Minimized = false;
	
	//
	bool ShowMiddle = true;
	
	//
	bool ShowImmediately = true;


public:
	WindowStyle( ) {};
	~WindowStyle( ) {};
};


}