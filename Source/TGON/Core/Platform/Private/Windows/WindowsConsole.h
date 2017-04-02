/**
 * filename WindowsConsole.h
 * author   ggomdyu
 * since    01/24/2016
 */

#pragma once
#include "../Generic/GenericConsole.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{

class TGON_API WindowsConsole : 
	public GenericConsole<WindowsConsole>
{
	friend GenericConsole<WindowsConsole>;

/**
 * @section Ctor/Dtor
 */
public:
    WindowsConsole() = delete;
    ~WindowsConsole() = delete;

/** 
 * @section Private command methods
 */ 
private:
	/*
	 * @brief           Write string to console.
	 * @param   str     String which you want to write to console
	*/
    static void WriteImpl(_In_ const char* str);
    static void WriteImpl(_In_ const wchar_t* str);
};

using TConsole = WindowsConsole;

} /* namespace tgon */