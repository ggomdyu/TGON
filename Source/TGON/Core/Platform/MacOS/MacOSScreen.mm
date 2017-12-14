#import "PrecompiledHeader.pch"
#import "../Screen.h"

#import <Foundation/NSArray.h>
#import <AppKit/NSScreen.h>
#import <vector>

#import "Core/Platform/Window.h"

namespace tgon
{
namespace platform
{
namespace
{

Screen ConvertNSScreenToScreen(NSScreen* nativeScreen)
{
    return Screen(
        nativeScreen.frame.size.width,
        nativeScreen.frame.size.height,
        [[[nativeScreen deviceDescription] objectForKey:@"NSDeviceBitsPerSample"] integerValue],
        0,
        ScreenOrientation::Landscape,
        false
    );
}

} /* namespace */

Screen GetPrimaryScreen()
{
    return ConvertNSScreenToScreen([NSScreen mainScreen]);
}

std::vector<Screen> GetAllScreen()
{
    NSArray<NSScreen*>* nativeScreens = [NSScreen screens];

    std::vector<Screen> screens;
    screens.reserve([nativeScreens count]);

    for (NSScreen* nativeScreen in nativeScreens)
    {
        screens.push_back(ConvertNSScreenToScreen(nativeScreen));
    }
    return screens;
}

} /* namespace platform */
} /* namespace tgon */
