#import "PrecompiledHeader.pch"

#import "../Path.h"

#import <Foundation/Foundation.h>

namespace tgon
{
namespace core
{

TGON_API std::string GetCurrentDirectory()
{
    NSString* path = [[NSFileManager defaultManager] currentDirectoryPath];
    return [path UTF8String];
}

//TGON_API int32_t GetCurrentDirectory(char* destPathStr, int32_t destPathStrBufferSize)
//{
//    NSString* path = [[NSFileManager defaultManager] currentDirectoryPath];
//    path.length
//}

TGON_API std::string GetUserDirectory()
{
    NSString* path = NSHomeDirectory();
    return [path UTF8String];
}

TGON_API std::string GetDesktopDirectory()
{
    NSArray<NSString*>* paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);

    if ([paths count] > 0)
    {
        return [[paths objectAtIndex: 0] UTF8String];
    }
    else
    {
        return std::string();
    }
}

} /* namespace core */
} /* namespace tgon */
