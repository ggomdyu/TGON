#pragma once

#include "Core/NonCopyable.h"
#include "Platform/Config.h"

namespace tg
{

class MacOSApplication :
    private NonCopyable
{
};

using PlatformApplication = MacOSApplication;

}
