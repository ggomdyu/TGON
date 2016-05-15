/*
* Author : Junho-Cha
* Date : 02/17/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <stdint.h>

namespace tgon
{


struct GraphicsStyle
{
	bool isWindowed = false;

	int32_t backBufferWidth = 0;	// 0 is window width size
	int32_t backBufferHeight = 0;	// 0 is window height size
};


}