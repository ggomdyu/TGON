#import "PrecompiledHeader.h"

#import <Foundation/NSString.h>
#import <Foundation/NSLocale.h>
#import <cstring>

#import "../Locale.h"

namespace tgon
{
    
int32_t GetLanguage(char* destStr, std::size_t destStrBufferSize)
{
    NSString* currentLanguageCode = [[NSLocale currentLocale] objectForKey:NSLocaleLanguageCode];
    [currentLanguageCode cStringUsingEncoding:NSUTF8StringEncoding];
    
    std::strncpy(destStr, currentLanguageCode.UTF8String, currentLanguageCode.length);
    
    return static_cast<std::int32_t>(currentLanguageCode.length);
}

} /* namespace tgon */
