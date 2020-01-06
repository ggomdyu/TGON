/**
 * @filename    AutoReleaseDC.h
 * @author      ggomdyu
 * @since       09/23/2017
 */

#pragma once
#include <Windows.h>

class AutoReleaseDC final
{
/* @section Public constructor */
public:
    AutoReleaseDC(HWND wndHandle);
	
/* @section Public destructor */
public:
    ~AutoReleaseDC();

/* @section Public operator */
public:
	operator HDC() const;

/* @section Private variable */
private:
	HWND m_wndHandle;
    HDC m_dcHandle;
};

inline AutoReleaseDC::AutoReleaseDC(HWND wndHandle) :
    m_wndHandle(wndHandle),
    m_dcHandle(::GetDC(wndHandle))
{
}

inline AutoReleaseDC::~AutoReleaseDC()
{
    ReleaseDC(m_wndHandle, m_dcHandle);
}

inline AutoReleaseDC::operator HDC() const
{
	return m_dcHandle;
}