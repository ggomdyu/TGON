#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

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