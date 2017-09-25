#import "PrecompiledHeader.pch"
#import "MacOSScreen.h"

#import <Foundation/NSArray.h>
#import <AppKit/NSScreen.h>
#import <vector>

#include "Core/Platform/Window.h"

namespace tgon
{
namespace platform
{
namespace
{

Screen ConvertNSScreenToScreen(NSScreen* nativeScreen)
{
    return Screen(
        nativeScreen.frame.size.width, // width
        nativeScreen.frame.size.height, // height
        [[[nativeScreen deviceDescription] objectForKey:@"NSDeviceBitsPerSample"] integerValue] // bitsPerPixel
        ,0,
        ScreenOrientation::Landscape
    );
}

}

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
