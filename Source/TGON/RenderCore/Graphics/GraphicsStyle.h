/*
* Author : Cha Junho
* Date : 02/17/2016
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


struct TGraphicsStyle
{
	static TGraphicsStyle DefaultStyle;

	bool isWindowed = false;

	int32_t backBufferWidth = 0;	// 0 is window width size
	int32_t backBufferHeight = 0;	// 0 is window height size
};


}