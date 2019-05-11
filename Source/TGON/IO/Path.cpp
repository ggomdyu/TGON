#include "PrecompiledHeader.h"

#include "Path.h"

namespace tgon
{

TGON_API std::string GetExtension(const char* srcPathStr, int32_t srcPathStrLen)
{
    int32_t iterIndex = srcPathStrLen - 1;

    while (true)
    {
        if (iterIndex < 0)
        {
            return std::string();
        }

        if (srcPathStr[iterIndex] == '.')
        {
            return std::string(&srcPathStr[iterIndex], srcPathStrLen - iterIndex);
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API std::string GetExtension(const char* srcPathStr)
{
    return GetExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)));
}

TGON_API int32_t GetExtension(const char* srcPathStr, int32_t srcPathStrLen, const char** destPathStr)
{
    int32_t iterIndex = srcPathStrLen - 1;
    
    while (true)
    {
        if (iterIndex < 0)
        {
            return -1;
        }

        if (srcPathStr[iterIndex] == '.')
        {
            *destPathStr = &srcPathStr[iterIndex];
            return srcPathStrLen - iterIndex;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API int32_t GetExtension(const char* srcPathStr, const char** destPathStr)
{
    return GetExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)), destPathStr);
}

TGON_API int32_t GetExtension(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr)
{
    const char* extensionStr = nullptr;
    int32_t destPathStrLen = GetExtension(srcPathStr, srcPathStrLen, &extensionStr);
    if (destPathStrLen == -1)
    {
        return -1;
    }

    memcpy(destPathStr, extensionStr, sizeof(srcPathStr[0]) * destPathStrLen);
    destPathStr[destPathStrLen] = '\0';

    return destPathStrLen;
}

TGON_API int32_t GetExtension(const char* srcPathStr, char* destPathStr)
{
    return GetExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)), destPathStr);
}

TGON_API std::string GetFileName(const char* srcPathStr, int32_t srcPathStrLen)
{
    std::string ret;

    int32_t iterIndex = srcPathStrLen - 1;

    while (true)
    {
        if (iterIndex <= 0)
        {
            ret.assign(&srcPathStr[iterIndex], srcPathStrLen);
            return ret;
        }
        else if (srcPathStr[iterIndex] == AltDirectorySeparatorChar ||
                 srcPathStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destPathStrLen = srcPathStrLen - (++iterIndex);

            ret.assign(&srcPathStr[iterIndex], destPathStrLen);
            return ret;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API std::string GetFileName(const char* srcPathStr)
{
    return GetFileName(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)));
}

TGON_API int32_t GetFileName(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr)
{
    int32_t iterIndex = srcPathStrLen - 1;

    while (true)
    {
        if (iterIndex <= 0)
        {
            memcpy(destPathStr, &srcPathStr[iterIndex], sizeof(srcPathStr[0]) * srcPathStrLen);
            destPathStr[srcPathStrLen] = '\0';

            return srcPathStrLen;
        }
        else if (srcPathStr[iterIndex] == AltDirectorySeparatorChar ||
                 srcPathStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destPathStrLen = srcPathStrLen - (++iterIndex);

            memcpy(destPathStr, &srcPathStr[iterIndex], sizeof(srcPathStr[0]) * destPathStrLen);
            destPathStr[destPathStrLen] = '\0';

            return destPathStrLen;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API int32_t GetFileName(const char* srcPathStr, char* destPathStr)
{
    return GetFileName(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)), destPathStr);
}

TGON_API std::string GetFileNameWithoutExtension(const char* srcPathStr, int32_t srcPathStrLen)
{
    const char* extensionStr = nullptr;
    int32_t extensionStrLen = GetExtension(srcPathStr, srcPathStrLen, &extensionStr);
    if (extensionStrLen == -1)
    {
        return std::string();
    }

    std::string ret;

    int32_t iterIndex = (srcPathStrLen - extensionStrLen) - 1;

    while (true)
    {
        if (iterIndex <= 0)
        {
            int32_t destPathStrLen = (srcPathStrLen - iterIndex) - extensionStrLen;

            ret.assign(&srcPathStr[iterIndex], destPathStrLen);
            return ret;
        }
        else if (srcPathStr[iterIndex] == AltDirectorySeparatorChar ||
                 srcPathStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destPathStrLen = (srcPathStrLen - (++iterIndex)) - extensionStrLen;

            ret.assign(&srcPathStr[iterIndex], destPathStrLen);
            return ret;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API std::string GetFileNameWithoutExtension(const char* srcPathStr)
{
    return GetFileNameWithoutExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)));
}

TGON_API int32_t GetFileNameWithoutExtension(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr)
{
    const char* extensionStr = nullptr;
    int32_t extensionStrLen = GetExtension(srcPathStr, srcPathStrLen, &extensionStr);
    if (extensionStrLen == -1)
    {
        return -1;
    }

    int32_t iterIndex = (srcPathStrLen - extensionStrLen) - 1;

    while (true)
    {
        if (iterIndex <= 0)
        {
            int32_t destPathStrLen = (srcPathStrLen - iterIndex) - extensionStrLen;

            memcpy(destPathStr, &srcPathStr[iterIndex], sizeof(srcPathStr[0]) * destPathStrLen);
            destPathStr[destPathStrLen] = '\0';

            return destPathStrLen;
        }
        else if (srcPathStr[iterIndex] == AltDirectorySeparatorChar ||
                 srcPathStr[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destPathStrLen = (srcPathStrLen - (++iterIndex)) - extensionStrLen;

            memcpy(destPathStr, &srcPathStr[iterIndex], sizeof(srcPathStr[0]) * destPathStrLen);
            destPathStr[destPathStrLen] = '\0';

            return destPathStrLen;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API int32_t GetFileNameWithoutExtension(const char* srcPathStr, char* destPathStr)
{
    return GetFileNameWithoutExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)), destPathStr);
}

TGON_API int32_t GetDirectoryName(const char* srcPathStr, char* destPathStr)
{
    return GetDirectoryName(srcPathStr, static_cast<int32_t>(strlen(srcPathStr)), destPathStr);
}

TGON_API int32_t GetDirectoryName(const char* srcPathStr, int32_t srcPathStrLen, char* destPathStr)
{
    int iterIndex = srcPathStrLen - 1;

    while (true)
    {
        if (iterIndex < 0)
        {
            return -1;
        }

        if (srcPathStr[iterIndex] == AltDirectorySeparatorChar)
        {
            memcpy(destPathStr, srcPathStr, sizeof(srcPathStr[0]) * iterIndex);
            destPathStr[iterIndex] = '\0';

            return iterIndex;
        }
        else
        {
            --iterIndex;
        }
    }
}

TGON_API bool HasExtension(const char* srcPathStr, int32_t srcPathStrLen)
{
    int iterIndex = srcPathStrLen - 1;

    while (true)
    {
        if (iterIndex < 0)
        {
            return false;
        }
        else
        {
            if (srcPathStr[iterIndex] == '.')
            {
                auto extensionWithoutPeriodLen = srcPathStrLen - (iterIndex + 1);
                return extensionWithoutPeriodLen > 0;
            }
            else
            {
                --iterIndex;
            }
        }
    }
}

TGON_API bool HasExtension(const char* srcPathStr)
{
    return HasExtension(srcPathStr, static_cast<int32_t>(std::strlen(srcPathStr)));
}

//TGON_API int32_t ChangeExtension(char* srcPathStr, int32_t srcPathStrLen, const char* extensionName)
//{
//    const char* extensionStr = nullptr;
//    int32_t destPathStrLen = GetExtension(srcPathStr, srcPathStrLen, &extensionStr);
//    if (destPathStrLen == -1)
//    {
//        return -1;
//    }
//
//
//}

} /* namespace tgon */
