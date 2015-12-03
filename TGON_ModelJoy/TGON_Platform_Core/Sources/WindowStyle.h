#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

struct WindowStyle
{
public:
	int x = 100;
	int y = 100;
	int width = 500;
	int height = 500;

	wchar_t* caption = L"";

	/* Shape */
	bool Resizeable = false;
	bool Popup = false;

	/* Show */
	bool Maximized = false;
	bool Minimized = false;
	bool Visible = true;
	bool ShowMiddle = true;
	bool TopMost = false;
};