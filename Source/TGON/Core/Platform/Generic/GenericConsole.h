/**
 * @filename    GenericConsole.h
 * @author      ggomdyu
 * @since       03/23/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {

class TGON_API GenericConsole
{
/*
 * @section Ctor/Dtor
 */
protected:
    GenericConsole() = delete;
    ~GenericConsole() = delete;

/** 
 * @section Protected methods
 */ 
public:
	/**
     * @brief               Writes text to console.
	 * @param [in]  str     TODO: WRITE
	 */
    static void Write(const char* format, ...);
    static void Write(const wchar_t* format, ...);

	/**
     * @brief               Writes text to console and jump to next line.
     * @param [in]  str     TODO: WRITE
	 */
    static void WriteLine(const char* format, ...);
    static void WriteLine(const wchar_t* format, ...);

/** 
 * @section Private variable
 */
protected:
    enum { BufferSize = 256 };

    static char m_buffer[BufferSize];
	static wchar_t m_wideBuffer[BufferSize];
};

decltype(GenericConsole::m_buffer) GenericConsole::m_buffer;
decltype(GenericConsole::m_wideBuffer) GenericConsole::m_wideBuffer;

} /* namespace tgon */