#include "PrecompiledHeader.h"

#include "Encoding.h"

namespace tgon
{

int32_t ASCII::GetCharCount(const char* str)
{
    return static_cast<int32_t>(std::char_traits<char>::length(str));
}

int32_t UTF16LE::GetCharCount(const char* str)
{
    return static_cast<int32_t>(std::char_traits<char16_t>::length(reinterpret_cast<const char16_t*>(str)));
}

int32_t UTF32::GetCharCount(const char* str)
{
    return static_cast<int32_t>(std::char_traits<char32_t>::length(reinterpret_cast<const char32_t*>(str)));
}

} /* namespace tgon */
