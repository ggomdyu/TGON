#include "PrecompiledHeader.h"

#include <Windows.h>

#include "../Locale.h"

namespace tgon
{

int32_t GetLanguage(char* destBuffer, std::size_t destStrBufferLen)
{
    int32_t destBufferLen = ::GetLocaleInfoA(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, destBuffer, static_cast<int>(destStrBufferLen));
    if (destBufferLen != 0)
    {
        return destBufferLen;
    }
    else
    {
        return -1;
    }
}

std::string GetLanguage()
{
    char languageStr[16];

    int32_t languageStrLen = GetLanguage(languageStr, std::extent<decltype(languageStr)>::value);
    return std::string(languageStr, languageStrLen);
}

} /* namespace tgon */