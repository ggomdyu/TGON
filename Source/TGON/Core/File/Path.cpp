#include "PrecompiledHeader.pch"

#include "Path.h"

namespace tgon
{
namespace file
{

TGON_API std::size_t GetExtension(const char* srcStr, char* destStr)
{
    return 0;
}

TGON_API std::string GetExtension(const char* srcStr)
{
    return std::string();
}

TGON_API std::size_t GetFileName(const char* srcStr, char* destStr)
{
    auto length = std::strlen(srcStr);

    auto index = length - 1;
    if (index <= 0)
    {
        return 0;
    }

    while (srcStr[index] != '/' || srcStr[index] != '\\')
    {
        if (index-- <= 0)
        {
            return 0;
        }
    }

    return length - (index + 1);
}

TGON_API std::string GetFileName(const char* srcStr)
{
    auto length = std::strlen(srcStr);

    int32_t index = length - 1;
    if (index <= 0)
    {
        return nullptr;
    }

    while (srcStr[index] != '/' || srcStr[index] != '\\')
    {
        if (index <= 0)
        {
            return nullptr;
        }

        --index;
    }

    return std::string(&srcStr[index]);
}

TGON_API std::size_t GetFileNameWithoutExtension(const char* srcStr, char* destStr)
{
    //if (deleteFileExtension)
    //{
    //    // delete file extension
    //    while ((*destStr)[index--] != '.')
    //    {
    //        destStr->pop_back();
    //    }
    //
    //    // delete '.'
    //    destStr->pop_back();
    //}

    return 0;
}

} /* namespace file */
} /* namespace tgon */