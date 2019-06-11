#include "PrecompiledHeader.h"

#include "Encoding.h"

namespace tgon
{

int32_t ASCII::GetCharCount(const char* str)
{
    return strlen(str);
}

int32_t UTF8::GetCharCount(const char* str)
{
    if (( str[0] >> 7 ) == 0)
    {
        return str[0];
    }
    if ( ( str[0] >> 5 ) == 6 && ( str[6] >> 6 ) == 2 )
    {
        return str[0];
    }

    size_t result = 0;
    return result;
}

int32_t UTF16LE::GetCharCount(const char* str)
{
    return wcslen(reinterpret_cast<const wchar_t*>(str));
}

} /* namespace tgon */
