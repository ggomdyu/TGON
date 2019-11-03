#include "PrecompiledHeader.h"

#include <array>

#include "Random/Random.h"
#include "Platform/Environment.h"

#include "Directory.h"
#include "Path.h"

namespace tgon
{

extern thread_local std::array<char, 16384> g_tempUtf8Buffer;

std::string Path::Combine(const std::string_view& path1, const std::string_view& path2)
{
    auto strLen = Combine(path1, path2, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Path::Combine(const std::string_view& path1, const std::string_view& path2, char* destStr, int32_t destStrBufferLen)
{
    if (path2.length() == 0)
    {
        int32_t destStrLen = static_cast<int32_t>(path1.length());
        if (destStrLen + 1 > destStrBufferLen)
        {
            return 0;
        }

        memcpy(destStr, path1.data(), static_cast<size_t>(destStrLen) + 1);
        return destStrLen;
    }

    if (path1.length() == 0 || IsPathRooted(path2))
    {
        if (static_cast<int32_t>(path2.length() + 1) > destStrBufferLen)
        {
            return 0;
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
            return 0;
        }

        destStr[index] = DirectorySeparatorChar;
        index += 1;
    }
    else
    {
        if (index + static_cast<int32_t>(path2.length()) > destStrBufferLen)
        {
            return 0;
        }
    }
    
    memcpy(destStr, path1.data(), path1.length());
    memcpy(&destStr[index], path2.data(), path2.length() + 1);
    
    return index + static_cast<int32_t>(path2.length());
}

std::string Path::ChangeExtension(const std::string_view& path, const std::string_view& extension)
{
    auto strLen = ChangeExtension(path, extension, g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

int32_t Path::ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr, int32_t destStrBufferLen)
{
    size_t extensionStartIndex = path.length();
    for (int32_t i = static_cast<int32_t>(extensionStartIndex) - 1; i >= 0; --i)
    {
        if (path[i] == '.')
        {
            extensionStartIndex = static_cast<size_t>(i);
            break;
        }
    }
    
    size_t requiredDestStrBufferLen = extensionStartIndex + extension.length() + 2;
    if (requiredDestStrBufferLen > destStrBufferLen)
    {
        return 0;
    }

    memcpy(destStr, path.data(), extensionStartIndex);
    memcpy(&destStr[extensionStartIndex + 1], extension.data(), extension.size());
    
    int32_t strLen = static_cast<int32_t>(extensionStartIndex + 1 + extension.size());
    destStr[strLen] = '\0';
    destStr[extensionStartIndex] = '.';
    
    return strLen;
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
        return 0;
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
    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
}

std::string Path::GetTempPath()
{
    auto strLen = GetTempPath(g_tempUtf8Buffer.data(), static_cast<int32_t>(g_tempUtf8Buffer.size()));
    if (strLen == -1)
    {
        return {};
    }

    return {g_tempUtf8Buffer.data(), static_cast<size_t>(strLen)};
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
            return 0;
        }
        
        memcpy(destStr, defaultTempPath, std::extent_v<decltype(defaultTempPath)>);
        return static_cast<int32_t>(std::extent_v<decltype(defaultTempPath)>) - 1;
    }
    
    if (Path::IsDirectorySeparator((*tempEnvVarValue)[tempEnvVarValue->length() - 1]))
    {
        if (tempEnvVarValue->length() + 1 > destStrBufferLen)
        {
            return 0;
        }
        
        memcpy(destStr, tempEnvVarValue->data(), tempEnvVarValue->size());
        destStr[tempEnvVarValue->size()] = '\0';
        
        return static_cast<int32_t>(tempEnvVarValue->size());
    }
    else
    {
        if (tempEnvVarValue->length() + 2 > destStrBufferLen)
        {
            return 0;
        }
        
        memcpy(destStr, tempEnvVarValue->data(), tempEnvVarValue->size());
        destStr[tempEnvVarValue->size()] = Path::DirectorySeparatorChar;
        destStr[tempEnvVarValue->size() + 1] = '\0';
        
        return static_cast<int32_t>(tempEnvVarValue->size());
    }
}

std::string Path::RemoveRelativeSegments(const std::string_view& path)
{
    std::string ret;
    for (decltype(path.length()) i = 0; i < path.length(); ++i)
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
                int32_t j = ret.length() == 0 ? 0 : static_cast<int32_t>(ret.length()) - 1;
                for (; j >= 0; --j)
                {
                    if (Path::IsDirectorySeparator(ret[j]))
                    {
                        ret.resize(static_cast<size_t>(j));
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
