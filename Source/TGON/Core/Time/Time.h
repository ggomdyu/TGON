/**
 * @file    Time.h
 * @author  ggomdyu
 * @since   05/15/2016
 * @brief   Set of Platform-agnostic Time interfaces.
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

namespace tgon
{

/* @brief   Returns OS excution elapsed time. */
TGON_API int64_t GetTickCount();

} /* namespace tgon */
