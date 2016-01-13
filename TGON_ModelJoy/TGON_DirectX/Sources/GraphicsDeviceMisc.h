/*
* 작성자 : 차준호
* 작성일 : 2016-01-10
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once

enum GraphicsDeviceProcessType
{
	kHardware,
	kSoftware,
};

struct GraphicsDeviceCreateParam
{
	HWND presentWnd;
	unsigned int width, height;
	bool isFullWindow;

	GraphicsDeviceProcessType gdpt;
};