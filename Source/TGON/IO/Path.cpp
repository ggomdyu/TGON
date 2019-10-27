#include "PrecompiledHeader.h"

#include <array>

#include "Random/Random.h"
#include "Platform/Environment.h"

#include "Path.h"
#include "Directory.h"

namespace tgon
{

extern thread_local std::array<char, 16384> g_tempUtf8Buffer;

std::string Path::Combine(const std::string_view& path1, const std::string_view& path2)
{
    auto strLen = Combine(path1, path2, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return std::string();
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
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

std::string Path::ChangeExtension(const std::string_view& path, const std::string_view& extension)
{
    auto strLen = ChangeExtension(path, extension, g_tempUtf8Buffer.data());
    if (strLen == -1)
    {
        return std::string();
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
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
    std::string collapsedString;
    if (!Path::IsPathRooted(path))
    {
        int32_t collapsedStringLen = Path::Combine(Directory::GetCurrentDirectory(), path, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
        collapsedString = RemoveRelativeSegments(std::string_view(&g_tempUtf8Buffer[0], collapsedStringLen));
    }
    else
    {
        collapsedString = RemoveRelativeSegments(path);
    }
    
    return collapsedString.length() == 0 ? "/" : collapsedString;
}

std::string Path::GetFullPath(const std::string_view& path, const std::string_view& basePath)
{
    auto combinedPath = Combine(basePath, path);
    if (combinedPath.length() == 0)
    {
        return combinedPath;
    }
    
    return GetFullPath(combinedPath);
}

int32_t Path::GetRandomFileName(char* destStr, int32_t destStrBufferLen)
{
    constexpr int32_t requiredDestStrBufferLen = 13;
    if (destStrBufferLen < requiredDestStrBufferLen)
    {
        return -1;
    }
    
    auto r = Random();
    int32_t strLen = requiredDestStrBufferLen - 1;
    for (int32_t i = 0; i < strLen; ++i)
    {
        destStr[i] = char(r.Next(0, 1) == 0 ? r.Next('a', 'z') : r.Next('0', '9'));
    }
    
    destStr[8] = '.';
    destStr[strLen] = '\0';

    return strLen;
}

std::string Path::GetRandomFileName()
{
    auto strLen = GetRandomFileName(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

std::string Path::GetTempPath()
{
    auto strLen = GetTempPath(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return std::string();
    }
    
    return std::string(g_tempUtf8Buffer.data(), static_cast<size_t>(strLen));
}

int32_t Path::GetTempPath(char* destStr, int32_t destStrBufferLen)
{
    const char tempEnvVarName[] = "TMPDIR";
    auto tempEnvVarValue = Environment::GetEnvironmentVariable(tempEnvVarName);
    if (!tempEnvVarValue)
    {
        const char defaultTempPath[] = "/tmp/";
        if (std::extent_v<decltype(defaultTempPath)> > destStrBufferLen)
        {
            return -1;
        }
        
        memcpy(destStr, defaultTempPath, std::extent_v<decltype(defaultTempPath)>);
        return static_cast<int32_t>(std::extent_v<decltype(defaultTempPath)>) - 1;
    }
    
    if (Path::IsDirectorySeparator((*tempEnvVarValue)[tempEnvVarValue->length() - 1]))
    {
        if (tempEnvVarValue->length() + 1 > destStrBufferLen)
        {
            return -1;
        }
        
        memcpy(destStr, tempEnvVarValue->data(), tempEnvVarValue->size());
        destStr[tempEnvVarValue->size()] = '\0';
        
        return static_cast<int32_t>(tempEnvVarValue->size());
    }
    else
    {
        if (tempEnvVarValue->length() + 2 > destStrBufferLen)
        {
            return -1;
        }
        
        memcpy(destStr, tempEnvVarValue->data(), tempEnvVarValue->size());
        destStr[tempEnvVarValue->size()] = Path::DirectorySeparatorChar;
        destStr[tempEnvVarValue->size() + 1] = '\0';
        
        return static_cast<int32_t>(tempEnvVarValue->size());
    }
}

bool Path::IsDirectorySeparator(char ch) noexcept
{
    return ch == AltDirectorySeparatorChar || ch == DirectorySeparatorChar;
}

bool Path::IsValidDriveChar(char ch) noexcept
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

std::string Path::RemoveRelativeSegments(const std::string_view& path)
{
    std::string ret;
    for (size_t i = 0; i < path.size(); ++i)
    {
        char c = path[i];
        if (Path::IsDirectorySeparator(c) && i + 1 < path.length())
        {
            // Ignore the '/'
            if (Path::IsDirectorySeparator(path[i + 1]))
            {
                continue;
            }
            
            // Ignore the "./"
            if (i + 2 >= path.length() || (Path::IsDirectorySeparator(path[i + 2]) && path[i + 1] == '.'))
            {
                ++i;
                continue;
            }
            
            if (i + 3 < path.length() && Path::IsDirectorySeparator(path[i + 3]) && path[i + 2] == '.' && path[i + 1] == '.')
            {
                size_t j = ret.length() == 0 ? 0 : ret.length() - 1;
                for (; j >= 0; --j)
                {
                    if (Path::IsDirectorySeparator(ret[j]))
                    {
                        ret.resize(j);
                        break;
                    }
                }
                
                if (j == 0)
                {
                    ret.resize(0);
                }
                
                i += 2;
                continue;
            }
        }

        // Normalize the directory separator
        if (c == Path::AltDirectorySeparatorChar)
        {
            c = Path::DirectorySeparatorChar;
        }
        
        ret += c;
    }

    return ret;
}

} /* namespace tgon */
