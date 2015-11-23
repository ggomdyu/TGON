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
	int nX = 100;
	int nY = 100;
	int nWidth = 500;
	int nHeight = 500;

	wchar_t* wsCaption = L"Default caption";
	
	/* Shape */
	bool bThickFrame = false;
	bool bPopUp = false;

	/* Show */
	bool bMaximized = false;
	bool bMinimized = false;
	bool bVisible = true;
	bool bShowMiddle = true;
	bool bTopMost = false;
};