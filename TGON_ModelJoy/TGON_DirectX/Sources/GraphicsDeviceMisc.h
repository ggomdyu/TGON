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
	GraphicsDeviceProcessType gdpt;

	unsigned int width;
	unsigned int height;
};