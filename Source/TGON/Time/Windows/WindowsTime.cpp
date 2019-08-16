#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "../Time.h"

namespace tgon
{

TGON_API int64_t GetTickCount()
{
    return GetTickCount64();
}

} /* namespace tgon */