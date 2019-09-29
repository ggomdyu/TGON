/**
 * @file    WindowsEnvironment.h
 * @author  ggomdyu
 * @since   08/25/2019
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   undef SetEnvironmentVariable
#   undef GetCurrentDirectory
#   undef GetCommandLine
#   undef GetEnvironmentVariable
#   undef GetSystemDirectory
#   undef GetUserName
#   undef GetTempPath
#endif
