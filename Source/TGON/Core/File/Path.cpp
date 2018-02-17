#include "PrecompiledHeader.pch"

#include "Path.h"

namespace tgon
{
namespace core
{

TGON_API int32_t GetExtension(const char* srcStr, int32_t srcStrLen, const char** destStr)
{
    int32_t iterIndex = srcStrLen - 1;

    while (true)
    {
        if (iterIndex < 0)
        {
            return -1;
        }

        if (srcStr[iterIndex] == '.')
        {
            *destStr = &srcStr[iterIndex];
            return srcStrLen - iterIndex;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API int32_t GetExtension(const char* srcStr, const char** destStr)
{
    return GetExtension(srcStr, static_cast<int32_t>(std::char_traits<typename std::remove_pointer<typename std::remove_const<decltype(srcStr)>::type>::type>::length(srcStr)), destStr);
}

TGON_API int32_t GetExtension(const char* srcStr, int32_t srcStrLen, char* destStr)
{
    const char* extensionStr = nullptr;
    int32_t destStrLen = GetExtension(srcStr, srcStrLen, &extensionStr);
    if (destStrLen == -1)
    {
        return -1;
    }

    memcpy(destStr, extensionStr, sizeof(srcStr[0]) * destStrLen);
    destStr[destStrLen] = '\0';

    return destStrLen;
}

TGON_API int32_t GetExtension(const char* srcStr, char* destStr)
{
    return GetExtension(srcStr, static_cast<int32_t>(std::char_traits<typename std::remove_pointer<typename std::remove_const<decltype(srcStr)>::type>::type>::length(srcStr)), destStr);
}

TGON_API int32_t GetFileName(const char* srcStr, int32_t srcStrLen, char* destStr)
{
    int32_t iterIndex = srcStrLen - 1;

    while (true)
    {
        if (srcStr[iterIndex] == AltDirectorySeparatorChar ||
            srcStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destStrLen = srcStrLen - (++iterIndex);

            memcpy(destStr, &srcStr[iterIndex], sizeof(srcStr[0]) * destStrLen);
            destStr[destStrLen] = '\0';

            return destStrLen;
        }
        else if (iterIndex <= 0)
        {
            memcpy(destStr, &srcStr[iterIndex], sizeof(srcStr[0]) * srcStrLen);
            destStr[srcStrLen] = '\0';

            return srcStrLen;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API int32_t GetFileName(const char* srcStr, char* destStr)
{
    return GetFileName(srcStr, static_cast<int32_t>(std::char_traits<typename std::remove_pointer<typename std::remove_const<decltype(srcStr)>::type>::type>::length(srcStr)), destStr);
}

TGON_API int32_t GetFileNameWithoutExtension(const char* srcStr, int32_t srcStrLen, char* destStr)
{
    const char* extensionStr = nullptr;
    int32_t extensionStrLen = GetExtension(srcStr, srcStrLen, &extensionStr);
    if (extensionStrLen == -1)
    {
        return -1;
    }

    int32_t iterIndex = (srcStrLen - extensionStrLen) - 1;

    while (true)
    {
        if (srcStr[iterIndex] == AltDirectorySeparatorChar ||
            srcStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destStrLen = (srcStrLen - (++iterIndex)) - extensionStrLen;

            memcpy(destStr, &srcStr[iterIndex], sizeof(srcStr[0]) * destStrLen);
            destStr[destStrLen] = '\0';

            return destStrLen;
        }
        else if (iterIndex <= 0)
        {
            int32_t destStrLen = (srcStrLen - iterIndex) - extensionStrLen;

            memcpy(destStr, &srcStr[iterIndex], sizeof(srcStr[0]) * destStrLen);
            destStr[destStrLen] = '\0';

            return destStrLen;
        }
        else
        {
            --iterIndex;
        }
    }

    return 0;
}

TGON_API int32_t GetFileNameWithoutExtension(const char* srcStr, char* destStr)
{
    return GetFileNameWithoutExtension(srcStr, static_cast<int32_t>(std::char_traits<typename std::remove_pointer<typename std::remove_const<decltype(srcStr)>::type>::type>::length(srcStr)), destStr);
}

TGON_API bool HasExtension(const char* srcStr, int32_t srcStrLen)
{
    int iterIndex = srcStrLen - 1;

    while (true)
    {
        if (iterIndex < 0)
        {
            return false;
        }
        else
        {
            if (srcStr[iterIndex] == '.')
            {
                auto extensionWithoutPeriodLen = srcStrLen - (iterIndex + 1);
                return extensionWithoutPeriodLen > 0;
            }
            else
            {
                --iterIndex;
            }
        }
    }
}

TGON_API bool HasExtension(const char* srcStr)
{
    return HasExtension(srcStr, static_cast<int32_t>(std::char_traits<typename std::remove_pointer<typename std::remove_const<decltype(srcStr)>::type>::type>::length(srcStr)));
}

} /* namespace core */
} /* namespace tgon */
