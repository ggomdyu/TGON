#import "PrecompiledHeader.pch"
#import "MacOSLocale.h"

#import <Foundation/NSString.h>
#import <Foundation/NSLocale.h>
#import <cstring>

namespace tgon
{
namespace platform
{

void GetLanguage(char* destBuffer, std::size_t bufferLength)
{
    NSLocale* currentLocale = [NSLocale currentLocale];
    NSString* currentLanguageCode = [currentLocale objectForKey:NSLocaleLanguageCode];
    
    [currentLanguageCode cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::strncpy(destBuffer, currentLanguageCode.UTF8String, currentLanguageCode.length);
}

} /* namespace platform */
} /* namespace tgon */
