#include "PrecompiledHeader.h"

#include <Foundation/Foundation.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <array>

#include "../Environment.h"

namespace tgon
{
namespace
{
    
int32_t GetSpecialDirectory(NSString* path, const std::string_view& postfixStr, char* destStr, int32_t destStrBufferLen)
{
    auto pathStrLen = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    if (pathStrLen + postfixStr.length() + 1 > destStrBufferLen)
    {
        return -1;
    }
    
    memcpy(destStr, path.UTF8String, pathStrLen);
    memcpy(&destStr[pathStrLen], postfixStr.data(), postfixStr.length() + 1);
    
    return static_cast<int32_t>(pathStrLen + postfixStr.length());
}

int32_t GetSpecialDirectory(NSSearchPathDirectory searchPathDirectory, NSSearchPathDomainMask pathDomainMask, const std::string_view& postfixStr, char* destStr, int32_t destStrBufferLen)
{
    NSArray<NSString*>* paths = NSSearchPathForDirectoriesInDomains(searchPathDirectory, pathDomainMask, YES);
    if ([paths count] <= 0)
    {
        return -1;
    }
    
    return GetSpecialDirectory([paths objectAtIndex: 0], postfixStr, destStr, destStrBufferLen);
}
    
} /* namespace */

bool Environment::SetEnvironmentVariable(const std::string_view& name, const std::string_view& value)
{
    return setenv(name.data(), value.data(), true) == 0;
}

int32_t Environment::GetEnvironmentVariable(const std::string_view& name, char* destStr, int32_t destStrBufferLen)
{
    const char* envValue = getenv(name.data());
    size_t envValueBytes = strlen(envValue);
    if (envValueBytes + 1 > destStrBufferLen)
    {
        return -1;
    }
    
    memcpy(destStr, envValue, envValueBytes + 1);
    
    return static_cast<int32_t>(envValueBytes);
}

int32_t Environment::GetCurrentManagedThreadId()
{
    // todo: impl
    return -1;
}

int32_t Environment::GetUserName(char* destStr, int32_t destStrBufferLen)
{
    if (getlogin_r(destStr, destStrBufferLen) != 0)
    {
        return -1;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

int32_t Environment::GetMachineName(char* destStr, int32_t destStrBufferLen)
{
    if (gethostname(destStr, destStrBufferLen) != 0)
    {
        return -1;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

int32_t Environment::GetUserDomainName(char* destStr, int32_t destStrBufferLen)
{
    if (getdomainname(destStr, destStrBufferLen) != 0)
    {
        return -1;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

int32_t Environment::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    NSString* path = [[NSFileManager defaultManager] currentDirectoryPath];
    auto pathStrLen = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    if (pathStrLen + 1 > destStrBufferLen)
    {
        return -1;
    }
    
    memcpy(destStr, path.UTF8String, pathStrLen + 1);
    return static_cast<int32_t>(pathStrLen);
}

int32_t Environment::GetFolderPath(SpecialFolder folder, char* destStr, int32_t destStrBufferLen)
{
    switch (folder)
    {
    case SpecialFolder::ApplicationData:
        return GetSpecialDirectory(NSHomeDirectory(), ".config", destStr, destStrBufferLen);
            
    case SpecialFolder::CommonApplicationData:
        return GetSpecialDirectory(@"/usr/share", "", destStr, destStrBufferLen);
       
    case SpecialFolder::Desktop:
    case SpecialFolder::DesktopDirectory:
        return GetSpecialDirectory(NSDesktopDirectory, NSUserDomainMask, "", destStr, destStrBufferLen);
            
    case SpecialFolder::Fonts:
        return GetSpecialDirectory(NSLibraryDirectory, NSUserDomainMask, "/Fonts", destStr, destStrBufferLen);

    case SpecialFolder::Favorites:
        return GetSpecialDirectory(NSLibraryDirectory, NSUserDomainMask, "/Favorites", destStr, destStrBufferLen);
            
    case SpecialFolder::InternetCache:
        return GetSpecialDirectory(NSCachesDirectory, NSUserDomainMask, "", destStr, destStrBufferLen);
            
    case SpecialFolder::ProgramFiles:
        return GetSpecialDirectory(@"/Applications", "", destStr, destStrBufferLen);
            
    case SpecialFolder::System:
        return GetSpecialDirectory(@"/System", "", destStr, destStrBufferLen);
        
    case SpecialFolder::UserProfile:
    case SpecialFolder::MyDocuments:
        return GetSpecialDirectory(NSHomeDirectory(), "", destStr, destStrBufferLen);
    
    case SpecialFolder::MyMusic:
        return GetSpecialDirectory(NSMusicDirectory, NSUserDomainMask, "", destStr, destStrBufferLen);
        
    case SpecialFolder::MyPictures:
        return GetSpecialDirectory(NSPicturesDirectory, NSUserDomainMask, "", destStr, destStrBufferLen);
            
    default:
        if (destStrBufferLen >= 1)
        {
            destStr[0] = '\0';
            return 0;
        }
        break;
    }
    
    return -1;
}

const std::string& Environment::GetCommandLine()
{
    return GetCommandLineArgs()[0];
}

const std::vector<std::string>& Environment::GetCommandLineArgs()
{
    static std::vector<std::string> commandLines = []()
    {
        std::vector<std::string> ret;
        for (NSString* commandLine in [[NSProcessInfo processInfo] arguments])
        {
            ret.push_back([commandLine UTF8String]);
        }
        
        return ret;
    } ();
    
    return commandLines;
}
    
int64_t Environment::GetTickCount()
{
    return mach_absolute_time() * 0.000001f;
}

bool Environment::Is64BitProcess()
{
    return sizeof(intptr_t) == 8;
}

bool Environment::Is64BitOperatingSystem()
{
    return Is64BitProcess();
}

std::string_view Environment::GetNewLine()
{
    char newLine[] = "\n";
    return {newLine, std::extent_v<decltype(newLine)> - 1};
}

int32_t Environment::GetSystemPageSize()
{
    return static_cast<int32_t>(getpagesize());
}

} /* namespace tgon */
