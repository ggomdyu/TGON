#import "PrecompiledHeader.h"

#import <Foundation/Foundation.h>

#import "../Path.h"

namespace tgon
{
    
thread_local char g_tempPathBuffer[PATH_MAX + 1];

TGON_API int32_t GetCurrentDirectory(char* destStr)
{
    NSString* path = [[NSFileManager defaultManager] currentDirectoryPath];
    auto pathStrBytes = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    memcpy(destStr, path.UTF8String, pathStrBytes + 1);
    return static_cast<int32_t>(pathStrBytes);
}

TGON_API int32_t GetUserDirectory(char* destStr)
{
    NSString* path = NSHomeDirectory();
    auto pathStrBytes = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    memcpy(destStr, path.UTF8String, pathStrBytes + 1);
    return static_cast<int32_t>(pathStrBytes);
}
    
TGON_API int32_t GetSpecialDirectory(NSSearchPathDirectory searchPathDirectory, NSSearchPathDomainMask pathDomainMask, char* destStr)
{
    NSArray<NSString*>* paths = NSSearchPathForDirectoriesInDomains(searchPathDirectory, pathDomainMask, YES);

    if ([paths count] > 0)
    {
        NSString* path = [paths objectAtIndex: 0];
        auto pathStrBytes = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
        
        memcpy(destStr, path.UTF8String, pathStrBytes + 1);
        return static_cast<int32_t>(pathStrBytes);
    }
    else
    {
        return -1;
    }
}

TGON_API int32_t GetDesktopDirectory(char* destStr)
{
    return GetSpecialDirectory(NSDesktopDirectory, NSUserDomainMask, destStr);
}

TGON_API int32_t GetFontsDirectory(char* destStr)
{
    int32_t strLen = GetSpecialDirectory(NSLibraryDirectory, NSSystemDomainMask, destStr);
    memcpy(&destStr[strLen], "/Fonts", sizeof(destStr[0]) * 7);

    return strLen + 6;
}

TGON_API int32_t GetMusicDirectory(char* destStr)
{
    return GetSpecialDirectory(NSMusicDirectory, NSUserDomainMask, destStr);
}
 
TGON_API int32_t GetPicturesDirectory(char* destStr)
{
    return GetSpecialDirectory(NSPicturesDirectory, NSUserDomainMask, destStr);
}

TGON_API int32_t GetVideosDirectory(char* destStr)
{
    return GetSpecialDirectory(NSMoviesDirectory, NSUserDomainMask, destStr);
}
    
TGON_API int32_t GetDocumentsDirectory(char* destStr)
{
    return GetSpecialDirectory(NSDocumentDirectory, NSUserDomainMask, destStr);
}
    
} /* namespace tgon */
