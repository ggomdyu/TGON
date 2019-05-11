#include "PrecompiledHeader.h"

#include "Path.h"

namespace tgon
{

extern thread_local char g_tempPathBuffer[];

TGON_API std::string GetExtension(const std::string_view& path)
{
    int32_t strLen = GetExtension(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API int32_t GetExtension(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());
    
    while (true)
    {
        if (--iterIndex < 0)
        {
            return -1;
        }

        if (path[iterIndex] == '.')
        {
            *destStr = path[iterIndex];
            return static_cast<int32_t>(path.length() - iterIndex);
        }
    }
}

TGON_API std::string GetFileName(const std::string_view& path)
{
    int32_t strLen = GetFileName(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API int32_t GetFileName(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex <= 0)
        {
            memcpy(destStr, &path[iterIndex], sizeof(destStr[0]) * (path.length() + 1));
            return static_cast<int32_t>(path.length());
        }
        else if (path[iterIndex] == AltDirectorySeparatorChar ||
                 path[iterIndex] == DirectorySeparatorChar)
        {
            auto destStrLen = path.length() - (++iterIndex);
            memcpy(destStr, &path[iterIndex], sizeof(path[0]) * (destStrLen + 1));

            return static_cast<int32_t>(destStrLen);
        }
    }
}

TGON_API std::string GetFileNameWithoutExtension(const std::string_view& path)
{
    int32_t strLen = GetFileNameWithoutExtension(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API int32_t GetFileNameWithoutExtension(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());
    int32_t extensionOffset = -1;

    while (true)
    {
        if (--iterIndex <= 0)
        {
            memcpy(destStr, &path[iterIndex], sizeof(destStr[0]) * (path.length() + 1));
            return static_cast<int32_t>(path.length());
        }
        else if (path[iterIndex] == AltDirectorySeparatorChar ||
                 path[iterIndex] == DirectorySeparatorChar)
        {
            auto destStrLen = path.length() - (++iterIndex);
            auto extensionLen = destStrLen - extensionOffset;

            memcpy(destStr, &path[iterIndex], sizeof(path[0]) * extensionLen);
            destStr[extensionLen] = '\0';

            return static_cast<int32_t>(destStrLen);
        }
        else if (extensionOffset == -1 && path[iterIndex] == '.')
        {
            extensionOffset = static_cast<int32_t>(path.length() - iterIndex);
        }
    }
}

TGON_API std::string GetDirectoryName(const std::string_view& path)
{
    int32_t strLen = GetDirectoryName(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API int32_t GetDirectoryName(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            return -1;
        }

        if (path[iterIndex] == AltDirectorySeparatorChar)
        {
            memcpy(destStr, &path[0], sizeof(path[0]) * iterIndex);
            destStr[iterIndex] = '\0';

            return iterIndex;
        }
    }
}

TGON_API bool HasExtension(const std::string_view& path)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            return false;
        }
        else
        {
            if (path[iterIndex] == '.')
            {
                return (path.length() - (iterIndex + 1)) > 0;
            }
        }
    }
}

TGON_API std::string ChangeExtension(const std::string_view& path, const std::string_view& extension)
{
    int32_t strLen = ChangeExtension(path, extension, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr)
{
    memcpy(&destStr[0], path.data(), sizeof(path[0]) * path.length() + 1);

    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            return static_cast<int32_t>(path.length());
        }
        else
        {
            if (path[iterIndex] == '.')
            {
                memcpy(&destStr[iterIndex + 1], extension.data(), sizeof(extension[0]) * (extension.length() + 1));

                auto pathExtensionLen = path.length() - (iterIndex + 1);
                return static_cast<int32_t>((path.length() - pathExtensionLen) + extension.length());
            }
        }
    }
}

TGON_API std::string GetCurrentDirectory()
{
    auto strLen = GetCurrentDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API std::string GetUserDirectory()
{
    auto strLen = GetUserDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API std::string GetDesktopDirectory()
{
    auto strLen = GetDesktopDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

TGON_API std::string GetFontsDirectory()
{
    auto strLen = GetFontsDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

} /* namespace tgon */
