#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>

#include "Platform/Environment.h"

#include "../Path.h"

namespace tgon
{

int32_t Path::GetFullPath(const std::string_view& path, char* destStr, int32_t destStrBufferLen)
{
    return 0;
}
    
gsl::span<const char> Path::GetInvalidFileNameChars() noexcept
{
    constexpr char invalidFileNameChars[] = {'\0', 'a'};
    return gsl::span(invalidFileNameChars, std::extent_v<decltype(invalidFileNameChars)> - 1);
}
    
gsl::span<const char> Path::GetInvalidPathChars() noexcept
{
    constexpr char invalidPathChars[] = {'\0'};
    return gsl::span(invalidPathChars, std::extent_v<decltype(invalidPathChars)> - 1);
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

} /* namespace tgon */
