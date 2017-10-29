#import "PrecompiledHeader.pch"
#import "MacOSLocale.h"

#import <Foundation/NSString.h>
#import <Foundation/NSLocale.h>
#import <cstring>

namespace tgon
{
namespace platform
{

void GetLanguage(char* destStr, std::size_t destStrBufferSize)
{
    NSString* currentLanguageCode = [[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode];
    [currentLanguageCode cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::strncpy(destStr, currentLanguageCode.UTF8String, currentLanguageCode.length);
}

} /* namespace platform */
} /* namespace tgon */
