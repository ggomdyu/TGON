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
	int X = 100;
	int Y = 100;
	int Width = 500;
	int Height = 500;

	wchar_t* Caption = L"";

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