/**
 * @file    EnvironmentTest.h
 * @author  ggomdyu
 * @since   08/22/2019
 */

#pragma once
#include <cassert>

#include "IO/Path.h"
#include "IO/File.h"
#include "Platform/Environment.h"
#include "Diagnostics/Debug.h"

#include "../Test.h"

namespace tgon
{

class EnvironmentTest :
    public Test
{
/**@section Method */
public:
    virtual void Evaluate() override
    {
#if TGON_PLATFORM_MACOS
        assert(Environment::GetPageSize() == 4096);
        assert(Environment::Is64BitProcess() == true);
        assert(Environment::Is64BitOperatingSystem() == true);
        assert(Environment::GetNewLine() == "\n");
#if TGON_PLATFORM_WINDOWS
#endif
    }
};

} /* namespace tgon */
