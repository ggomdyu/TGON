#include "PrecompiledHeader.h"

#include "Path.h"

namespace tgon
{
    
thread_local char g_tempPathBuffer[2048];

int32_t Path::Combine(const std::string_view& path1, const std::string_view& path2, char* destStr)
{
    auto seperator = path1[path1.length() - 1];
    
    int32_t index = static_cast<int32_t>(path1.size());
    
    bool hasSeperator = seperator == DirectorySeparatorChar || seperator == AltDirectorySeparatorChar;
    if (hasSeperator)
    {
        destStr[index] = AltDirectorySeparatorChar;
        index += 1;
    }
    
    memcpy(destStr, path1.data(), path1.length());
    memcpy(&destStr[index + 1], path2.data(), path2.length() + 1);
    
    return index + path2.length();
}

std::string_view Path::GetExtension(const std::string_view& path)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());
    
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
    int32_t strLen = GetFileName(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

int32_t Path::GetFileName(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex <= 0)
        {
            memcpy(destStr, &path.data()[0], sizeof(destStr[0]) * (path.length() + 1));
            return static_cast<int32_t>(path.length());
        }

        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            auto destStrLen = path.length() - (++iterIndex);
            memcpy(destStr, &path[iterIndex], sizeof(path[0]) * (destStrLen + 1));

            return static_cast<int32_t>(destStrLen);
        }
    }
}

std::string Path::GetFileNameWithoutExtension(const std::string_view& path)
{
    int32_t strLen = GetFileNameWithoutExtension(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

int32_t Path::GetFileNameWithoutExtension(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());
    int32_t extensionStartIndex = iterIndex;
    
    while (true)
    {
        if (--iterIndex <= 0)
        {
            memcpy(destStr, path.data(), extensionStartIndex);
            return extensionStartIndex;
        }

        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            int32_t destStrLen = extensionStartIndex - (iterIndex + 1);
            
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
    int32_t strLen = GetDirectoryName(path, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

int32_t Path::GetDirectoryName(const std::string_view& path, char* destStr)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            destStr[0] = '\0';
            return 0;
        }
        
        if (path[iterIndex] == AltDirectorySeparatorChar)
        {
            memcpy(destStr, &path[0], sizeof(path[0]) * iterIndex);
            destStr[iterIndex] = '\0';

            return iterIndex;
        }
    }
}

bool Path::HasExtension(const std::string_view& path)
{
    int32_t iterIndex = static_cast<int32_t>(path.length());

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
    int32_t strLen = ChangeExtension(path, extension, &g_tempPathBuffer[0]);
    return std::string(g_tempPathBuffer, strLen);
}

int32_t Path::ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr)
{
    if (path.length() == 0)
    {
        destStr[0] = '\0';
        return 0;
    }

    std::string_view newExtension = extension[0] == '.' ? extension.substr(1) : extension;

    int32_t iterIndex = static_cast<int32_t>(path.length());
    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == '.')
        {
            memcpy(destStr, path.data(), iterIndex + 1);
            memcpy(&destStr[iterIndex + 1], newExtension.data(), newExtension.length() + 1);

            return static_cast<int32_t>(iterIndex + 1 + newExtension.length());
        }
    }

    memcpy(destStr, path.data(), path.length());
    memcpy(&destStr[path.length() + 1], newExtension.data(), newExtension.length() + 1);
    destStr[path.length()] = '.';

    return static_cast<int32_t>(path.length() + 1 + newExtension.length());
}

std::string Path::GetCurrentDirectory()
{
    auto strLen = GetCurrentDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

std::string Path::GetUserDirectory()
{
    auto strLen = GetUserDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

std::string Path::GetDesktopDirectory()
{
    auto strLen = GetDesktopDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

std::string Path::GetFontsDirectory()
{
    auto strLen = GetFontsDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}
    
std::string Path::GetMusicDirectory()
{
    auto strLen = GetMusicDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}
    
std::string Path::GetPicturesDirectory()
{
    auto strLen = GetPicturesDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

std::string Path::GetVideosDirectory()
{
    auto strLen = GetVideosDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

std::string Path::GetDocumentsDirectory()
{
    auto strLen = GetDocumentsDirectory(g_tempPathBuffer);
    return std::string(g_tempPathBuffer, strLen);
}

} /* namespace tgon */
