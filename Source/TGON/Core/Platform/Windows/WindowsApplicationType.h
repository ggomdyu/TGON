/**
 * @filename    WindowsApplicationType.h
 * @author      ggomdyu
 * @since       04/04/2017
 */

#pragma once
#include "../Generic/GenericApplicationType.h"

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{
namespace platform
{

enum class YesNoPopupEvent
{
    Yes = IDYES,
    No = IDNO,
};

} /* namespace platform */
} /* namespace tgon */