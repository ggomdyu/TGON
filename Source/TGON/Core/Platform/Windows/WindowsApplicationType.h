/**
 * @filename    WindowsApplicationType.h
 * @author      ggomdyu
 * @since       06/11/2018
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

namespace tgon 
{

enum class MessageBoxIcon
{
    No = -1,
    Informational = MB_ICONQUESTION,
    Warning = MB_ICONEXCLAMATION,
};

} /* namespace tgon */