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

TGON_API std::string GetUserDirectory()
{
    NSString* path = NSHomeDirectory();
    return [path UTF8String];
}

TGON_API std::string GetDesktopDirectory()
{
    NSArray<NSString*>* paths = NSSearchPathForDirectoriesInDomains(NSDesktopDirectory, NSUserDomainMask, YES);

    if ([paths count] <= 0)
    {
        return std::string();
    }
    else
    {
        return [[paths objectAtIndex: 0] UTF8String];
    }
}

} /* namespace core */
} /* namespace tgon */
