#import "IOSLocale.h"

#import <Foundation/NSString.h>
#import <Foundation/NSLocale.h>
#import <cstring>

namespace tgon
{
namespace platform
{
namespace ios
{

void GetLanguage(char* destBuffer, std::size_t bufferLength)
{
    NSLocale* currentLocale = [NSLocale currentLocale];
    NSString* currentLanguageCode = [currentLocale objectForKey:NSLocaleLanguageCode];
    
    [currentLanguageCode cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::strncpy(destBuffer, currentLanguageCode.UTF8String, currentLanguageCode.length);
}

} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */
