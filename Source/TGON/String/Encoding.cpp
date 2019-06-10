#include "PrecompiledHeader.h"

#include "Encoding.h"

namespace tgon
{

int32_t ASCII::GetCharCount(const char* str)
{
    return strlen(str);
}

int32_t UTF8::GetCharCount(const char* string)
{
    size_t result = 0;
    return result;
}

int32_t UTF16LE::GetCharCount(const char* str)
{
    return wcslen(reinterpret_cast<const wchar_t*>(str));
}

} /* namespace tgon */
