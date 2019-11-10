/**
 * @file    Windows.h
 * @author  ggomdyu
 * @since   11/03/2019
 */

#pragma once
#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef CreateDirectory
#undef SetEnvironmentVariable
#undef GetEnvironmentVariable