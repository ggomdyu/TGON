#import "PrecompiledHeader.h"

#import <Foundation/Foundation.h>

#import "../Path.h"

namespace tgon
{

TGON_API int32_t Path::GetCurrentDirectory(char* destStr)
{
    NSString* path = [[NSFileManager defaultManager] currentDirectoryPath];
    auto pathStrBytes = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    memcpy(destStr, path.UTF8String, pathStrBytes + 1);
    return static_cast<int32_t>(pathStrBytes);
}

TGON_API int32_t Path::GetUserDirectory(char* destStr)
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

TGON_API int32_t Path::GetDesktopDirectory(char* destStr)
{
    return GetSpecialDirectory(NSDesktopDirectory, NSUserDomainMask, destStr);
}

TGON_API int32_t Path::GetFontsDirectory(char* destStr)
{
    int32_t strLen = GetSpecialDirectory(NSLibraryDirectory, NSSystemDomainMask, destStr);
    memcpy(&destStr[strLen], "/Fonts", sizeof(destStr[0]) * 7);

    return strLen + 6;
}

TGON_API int32_t Path::GetMusicDirectory(char* destStr)
{
    return GetSpecialDirectory(NSMusicDirectory, NSUserDomainMask, destStr);
}
 
TGON_API int32_t Path::GetPicturesDirectory(char* destStr)
{
    return GetSpecialDirectory(NSPicturesDirectory, NSUserDomainMask, destStr);
}

TGON_API int32_t Path::GetVideosDirectory(char* destStr)
{
    return GetSpecialDirectory(NSMoviesDirectory, NSUserDomainMask, destStr);
}
    
TGON_API int32_t Path::GetDocumentsDirectory(char* destStr)
{
    return GetSpecialDirectory(NSDocumentDirectory, NSUserDomainMask, destStr);
}
    
} /* namespace tgon */
