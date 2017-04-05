/**
 * filename WindowsApplicationFwd.h
 * author   ggomdyu
 * since    04/04/2017
 */

#pragma once
#include "../Generic/GenericApplicationFwd.h"

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include <Windows.h>

namespace tgon
{

enum class TPopupEvent
{
    Ok = IDOK,
    Yes = IDYES,
    No = IDNO,
};

} /* namespace tgon */
