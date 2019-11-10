#include "PrecompiledHeader.h"

#include <array>
#include <Foundation/Foundation.h>
#include <mach/mach_time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <pthread.h>
#include <execinfo.h>

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
        return 0;
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
        return 0;
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
    if (envValue == nullptr)
    {
        return -1;
    }
    
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
    return static_cast<int32_t>(pthread_mach_thread_np(pthread_self()));
}

int32_t Environment::GetUserName(char* destStr, int32_t destStrBufferLen)
{
    if (getlogin_r(destStr, destStrBufferLen) != 0)
    {
        return 0;
    }
    
    return static_cast<int32_t>(strlen(destStr));
}

int32_t Environment::GetMachineName(char* destStr, int32_t destStrBufferLen)
{
    if (gethostname(destStr, destStrBufferLen) != 0)
    {
        return 0;
    }
    
    utsname name;
    uname(&name);
    
    int32_t nodeNameLen = static_cast<int32_t>(strlen(name.nodename));
    if (nodeNameLen + 1 > destStrBufferLen)
    {
        return 0;
    }
    
    memcpy(destStr, name.nodename, nodeNameLen + 1);
    
    return nodeNameLen;
}

int32_t Environment::GetUserDomainName(char* destStr, int32_t destStrBufferLen)
{
    return GetMachineName(destStr, destStrBufferLen);
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
        return 0;
    }
    
    return 0;
}

const std::string& Environment::GetCommandLine()
{
    static std::string commandLine = []()
    {
        std::string ret;
        for (NSString* commandLine in [[NSProcessInfo processInfo] arguments])
        {
            ret += [commandLine UTF8String];
            ret += " ";
        }
        
        ret.pop_back();
        return ret;
    } ();
    
    return commandLine;
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
    return "\n";
}

int32_t Environment::GetSystemPageSize()
{
    return static_cast<int32_t>(getpagesize());
}

int32_t Environment::GetStackTrace(char* destStr, int32_t destStrBufferLen)
{
    std::array<void*, 2048> addr;
    int numFrames = backtrace(addr.data(), static_cast<int>(addr.size()));
    if (numFrames <= 0)
    {
        return 0;
    }
    
    int32_t destStrLen = 0;
    char** symbols = backtrace_symbols(addr.data(), numFrames);
    for (int i = 0; i < numFrames; ++i)
    {
        destStrLen += sprintf(&destStr[destStrLen], "%s\n", symbols[i]);
    }
    
    free(symbols);
    
    return destStrLen;
}

} /* namespace tgon */
