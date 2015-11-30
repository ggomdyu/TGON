#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
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