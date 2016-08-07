/*
* Author : Cha Junho
* Date : 02/17/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <cstdint>


namespace tgon
{


struct GraphicsProperty
{
public:
	//static const GraphicsProperty DefaultStyle;

public:
	// Set if you want to make full screen window
	bool enableFullScreen = false;

	// Set if you want to toggle full screen on run-time
	bool enableToggleFullScreen = true;

	// Set swap chain buffer's width
	// 0 is window width size
	int32_t bufferWidth = 0;
	
	// Set swap chain buffer's height
	// 0 is window height size
	int32_t bufferHeight = 0;
};


}