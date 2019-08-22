#include "PrecompiledHeader.h"

#include "Path.h"

namespace tgon
{

extern std::array<char, 16384> g_tempUtf8Buffer;

std::string Path::Combine(const std::string_view& path1, const std::string_view& path2)
{
    auto strLen = Combine(path1, path2, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

int32_t Path::Combine(const std::string_view& path1, const std::string_view& path2, char* destStr, int32_t destStrBufferLen)
{
    if (path2.length() == 0)
    {
        int32_t destStrLen = static_cast<int32_t>(path1.length());
        if (destStrLen + 1 > destStrBufferLen)
        {
            return -1;
        }

        memcpy(destStr, path1.data(), static_cast<size_t>(destStrLen + 1));
        return destStrLen;
    }

    if (path1.length() == 0 || IsPathRooted(path2))
    {
        if (static_cast<int32_t>(path2.length() + 1) > destStrBufferLen)
        {
            return -1;
        }

        memcpy(destStr, path2.data(), path2.length() + 1);
        return static_cast<int32_t>(path2.length());
    }

    auto index = static_cast<int32_t>(path1.size());

    auto path1Seperator = path1[path1.length() - 1];
    auto path2Seperator = path2[0];
    bool hasSeperator = (path1Seperator == DirectorySeparatorChar) || (path1Seperator == AltDirectorySeparatorChar) || (path2Seperator == DirectorySeparatorChar) || (path2Seperator == AltDirectorySeparatorChar);
    if (!hasSeperator)
    {
        if (index + 1 + static_cast<int32_t>(path2.length()) > destStrBufferLen)
        {
            return -1;
        }

        destStr[index] = DirectorySeparatorChar;
        index += 1;
    }
    else
    {
        if (index + static_cast<int32_t>(path2.length()) > destStrBufferLen)
        {
            return -1;
        }
    }
    
    memcpy(destStr, path1.data(), path1.length());
    memcpy(&destStr[index], path2.data(), path2.length() + 1);
    
    return index + static_cast<int32_t>(path2.length());
}

bool Path::IsPathRooted(const std::string_view& path)
{
    return (path.length() >= 1 && IsDirectorySeparator(path[0])) || (path.length() >= 2 && IsValidDriveChar(path[0]) && path[1] == VolumeSeparatorChar);
}

std::string_view Path::GetExtension(const std::string_view& path)
{
    auto iterIndex = static_cast<int32_t>(path.length());
    
    while (true)
    {
        if (--iterIndex < 0)
        {
            return {"", 0};
        }

        if (path[iterIndex] == '.')
        {
            return path.substr(iterIndex);
        }
    }
}

std::string Path::GetFileName(const std::string_view& path)
{
    auto strLen = GetFileName(path, g_tempUtf8Buffer.data(), g_tempUtf8Buffer.size());
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

int32_t Path::GetFileName(const std::string_view& path, char* destStr, int32_t destStrBufferLen)
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex <= 0)
        {
            int32_t destStrLen = static_cast<int32_t>(path.length());
            if (destStrLen + 1 > destStrBufferLen)
            {
                return -1;
            }

            memcpy(destStr, &path.data()[0], static_cast<size_t>(destStrLen));
            destStr[destStrLen] = '\0';

            return static_cast<int32_t>(path.length());
        }

        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            auto destStrLen = static_cast<int32_t>(path.length()) - (++iterIndex);
            if (destStrLen + 1 > destStrBufferLen)
            {
                return -1;
            }

            memcpy(destStr, &path[iterIndex], static_cast<size_t>(destStrLen));
            destStr[destStrLen] = '\0';

            return destStrLen;
        }
    }
}

std::string Path::GetFileNameWithoutExtension(const std::string_view& path)
{
    auto strLen = GetFileNameWithoutExtension(path, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

int32_t Path::GetFileNameWithoutExtension(const std::string_view& path, char* destStr, int32_t destStrBufferLen)
{
    auto iterIndex = static_cast<int32_t>(path.length());
    auto extensionStartIndex = iterIndex;
    
    while (true)
    {
        if (--iterIndex <= 0)
        {
            if (extensionStartIndex > destStrBufferLen)
            {
                return -1;
            }

            memcpy(destStr, path.data(), extensionStartIndex);
            return extensionStartIndex;
        }

        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destStrLen = extensionStartIndex - (iterIndex + 1);
            if (destStrLen + 1 > destStrBufferLen)
            {
                return -1;
            }
            
            memcpy(destStr, &path[iterIndex + 1], destStrLen);
            destStr[destStrLen] = '\0';
            
            return destStrLen;
        }

        if (path[iterIndex] == '.' && path.data()[extensionStartIndex] == '\0')
        {
            extensionStartIndex = iterIndex;
        }
    }
}

std::string Path::GetDirectoryName(const std::string_view& path)
{
    auto strLen = GetDirectoryName(path, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

int32_t Path::GetDirectoryName(const std::string_view& path, char* destStr, int32_t destStrBufferLen)
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            if (1 > destStrBufferLen)
            {
                return -1;
            }

            destStr[0] = '\0';
            return 0;
        }
        
        if (path[iterIndex] == AltDirectorySeparatorChar)
        {
            if (iterIndex + 1 > destStrBufferLen)
            {
                return -1;
            }

            memcpy(destStr, &path[0], iterIndex);
            destStr[iterIndex] = '\0';

            return iterIndex;
        }
    }
}

bool Path::HasExtension(const std::string_view& path)
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            return false;
        }

        if (path[iterIndex] == '.')
        {
            return (path.length() - (iterIndex + 1)) > 0;
        }
    }
}

std::string Path::ChangeExtension(const std::string_view& path, const std::string_view& extension)
{
    auto strLen = ChangeExtension(path, extension, g_tempUtf8Buffer.data());
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

int32_t Path::ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr)
{
    if (path.length() == 0)
    {
        destStr[0] = '\0';
        return 0;
    }

    auto newExtension = extension[0] == '.' ? extension.substr(1) : extension;

    int32_t iterIndex = static_cast<int32_t>(path.length());
    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == '.')
        {
            memcpy(destStr, path.data(), iterIndex + 1);
            memcpy(&destStr[iterIndex + 1], newExtension.data(), newExtension.length() + 1);

            return iterIndex + 1 + static_cast<int32_t>(newExtension.length());
        }
    }

    memcpy(destStr, path.data(), path.length());
    memcpy(&destStr[path.length() + 1], newExtension.data(), newExtension.length() + 1);
    destStr[path.length()] = '.';

    return static_cast<int32_t>(path.length() + 1 + newExtension.length());
}

std::string Path::GetFullPath(const std::string_view& path)
{
    auto strLen = GetFullPath(path, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(g_tempUtf8Buffer.data(), strLen);
}

bool Path::IsDirectorySeparator(char ch) noexcept
{
    return ch == AltDirectorySeparatorChar || ch == DirectorySeparatorChar;
}

bool Path::IsValidDriveChar(char ch) noexcept
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

} /* namespace tgon */