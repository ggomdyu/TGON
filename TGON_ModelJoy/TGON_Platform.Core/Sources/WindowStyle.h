#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

namespace tgon
{


struct WindowStyle
{
	/* Window creation props */
	wchar_t* caption = L"";

	int x = 100;
	int y = 100;
	int width = 500;
	int height = 500;

	/* Shape */
	bool Resizeable = false;
	bool Popup = false;
	bool Maximized = false;
	bool Minimized = false;

	/* Show */
	bool Visible = true;
	bool ShowMiddle = true;
	bool TopMost = false;
};


}