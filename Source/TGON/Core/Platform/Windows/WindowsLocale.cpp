#include "PrecompiledHeader.pch"

#include <Windows.h>

#include "../Base/BaseLocale.h"

namespace tgon
{
namespace platform
{

void GetLanguage(char* destBuffer, std::size_t bufferLength)
{
    ::GetLocaleInfoA(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, destBuffer, bufferLength);
}

} /* namespace platform */
} /* namespace tgon */