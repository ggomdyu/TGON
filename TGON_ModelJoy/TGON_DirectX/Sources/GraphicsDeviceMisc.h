#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-10
* ���� ���� :
* ���� ������ :
*/

enum GraphicsDeviceProcessType
{
	kHardware,
	kSoftware,
};

struct GraphicsDeviceCreateParam
{
	HWND presentWnd;
	GraphicsDeviceProcessType gdpt;
	uint32_t width;
	uint32_t height;
};