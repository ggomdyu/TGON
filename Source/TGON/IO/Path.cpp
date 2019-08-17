#include "PrecompiledHeader.h"

#include "Path.h"

namespace tgon
{
    
thread_local char g_tempPathBuffer[2048];

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
            memcpy(destStr, &path[iterIndex], sizeof(destStr[0]) * (path.length() + 1));
            return static_cast<int32_t>(path.length());
        }
        else if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
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
        else if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            int32_t strLen = extensionStartIndex - (iterIndex + 1);
            
            memcpy(destStr, &path[iterIndex + 1], strLen);
            destStr[strLen] = '\0';
            
            return strLen;
        }
        else if (path[iterIndex] == '.' && path[extensionStartIndex] == '\0')
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
        else if (path[iterIndex] == AltDirectorySeparatorChar)
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
        else
        {
            if (path[iterIndex] == '.')
            {
                return (path.length() - (iterIndex + 1)) > 0;
            }
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
    int32_t iterIndex = static_cast<int32_t>(path.length());

    while (true)
    {
        if (--iterIndex < 0)
        {
            memcpy(destStr, path.data(), path.length());
            
            dest
            
            return 0;
        }
        else if (path[iterIndex] == '.')
        {
            memcpy(&destStr[iterIndex + 1], extension.data(), sizeof(extension[0]) * (extension.length() + 1));

            auto pathExtensionLen = path.length() - (iterIndex + 1);
            return static_cast<int32_t>((path.length() - pathExtensionLen) + extension.length());
        }
    }
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
