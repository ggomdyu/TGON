/*
* 작성자 : 차준호
* 작성일 : 2016-02-17
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
namespace tgon
{


struct GraphicsDeviceProp
{
	bool isWindowed = 0;

	int32_t backBufferWidth = 0;	// 0 is window width size
	int32_t backBufferHeight = 0;	// 0 is window height size
};


}