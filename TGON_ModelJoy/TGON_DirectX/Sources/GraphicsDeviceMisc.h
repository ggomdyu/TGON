/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-10
* ���� ���� :
* ���� ������ :
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