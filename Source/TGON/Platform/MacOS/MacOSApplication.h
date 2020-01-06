/**
 * @file    MacOSApplication.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#include "Core/NonCopyable.h"
#include "Platform/Config.h"

namespace tgon
{

class MacOSApplication :
    private NonCopyable
{
};

using PlatformApplication = MacOSApplication;

} /* namespace tgon */
