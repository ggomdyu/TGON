/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 김태우
* 최종 수정일 : 2015-04-26
*/

#ifndef DEFINE_H
#define DEFINE_H
#define CLASS_NAME L"ModelJoy"
#define WINDOW_NAME L"ModelJoy"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080

struct CUSTOMVERTEX
{
	FLOAT m_fX, m_fY, m_fZ, m_fRHW;
	DWORD m_dwColor;
};

#endif