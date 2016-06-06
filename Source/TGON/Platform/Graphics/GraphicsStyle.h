/*
* Author : Junho-Cha
* Date : 02/17/2016
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


struct GraphicsStyle
{
	int32_t backBufferWidth = 0;	// 0 is owner window's width size
	int32_t backBufferHeight = 0;	// 0 is owner window's height size
	
	bool isWindowed = true;
};


}