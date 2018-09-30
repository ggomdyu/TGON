/**
 * @file    WindowsDebugMisc.h
 * @author  ggomdyu
 * @since   09/30/2018
 */

#pragma once

namespace tgon
{

/**
 * @brief   Prevent to modify global exception filter.
 * @see     http://blog.kalmbachnet.de/?postid=75
 *          http://blog.kalmbach-software.de/2008/04/02/unhandled-exceptions-in-vc8-and-above-for-x86-and-x64/
 *          http://blog.kalmbach-software.de/2013/05/23/improvedpreventsetunhandledexceptionfilter/
 */
bool PreventSetUnhandledExceptionFilter();


} /* namespace tgon */