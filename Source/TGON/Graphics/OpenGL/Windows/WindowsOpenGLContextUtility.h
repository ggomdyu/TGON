/**
 * @file    WindowsOpenGLContextUtility.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{

HGLRC MakeOldGLRC(HDC dcHandle);
HGLRC MakeNewGLRC(HDC dcHandle);

} /* namespace tgon */
