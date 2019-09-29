/**
 * @file    WindowsDirectory.h
 * @author  ggomdyu
 * @since   09/28/2019
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   undef GetCurrentDirectory
#endif
