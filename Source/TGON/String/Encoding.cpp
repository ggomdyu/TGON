#include "PrecompiledHeader.h"

#include "Encoding.h"

namespace tgon
{

int32_t ASCII::GetCharCount(const char* str)
{
    return static_cast<int32_t>(strlen(str));
}

int32_t UTF16LE::GetCharCount(const char* str)
{
    return static_cast<int32_t>(wcslen(reinterpret_cast<const wchar_t*>(str)));
}

} /* namespace tgon */
