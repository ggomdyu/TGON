#import "iOSScreen.h"

#import <UIKit/UIScreen.h>

namespace tgon
{
namespace platform
{
    
TGON_API int32_t GetMonitorCount()
{
    return 1;
}

TGON_API void GetScreenResolution(int32_t* width, int32_t* height)
{
    CGSize screenResolution = [[UIScreen mainScreen] bounds].size;
    
    *width = screenResolution.width;
    *height = screenResolution.height;
}
    
TGON_API float GetScaleFactor()
{
    return [[UIScreen mainScreen] scale];
}

} /* namespace platform */
} /* namespace tgon */
