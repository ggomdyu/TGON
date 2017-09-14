//
//  main.m
//  ThousandParty
//
//  Created by 차준호 on 2017. 9. 10..
//  Copyright © 2017년 ggomdyu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <iostream>
#import <ctime>
#include <cmath>

#import "Core/Platform/MacOS/MacOSAppDelegate.h"
#import "Core/Platform/Window.h"
#import "Core/Platform/Locale.h"
#import "Core/Random/Random.h"
#import "Core/Math/Vector3.h"
#import "Core/Math/Point.h"
#import "Core/Math/Extent.h"
#import "Core/Math/Rect.h"

using tgon::platform::Window;

//class MyCustomWindow :
//    public Window
//{
//public:
//    using Window::Window;
//
//public:
//    virtual void OnResize(int32_t width, int32_t height) override
//    {
//        std::cout << width << " " << height << std::endl;
//    }
//};
//
//int main(int argc, const char * argv[])
//{
//    @autoreleasepool
//    {
//        using namespace tgon;
//        using namespace tgon::math;
//
//        // Initialize NSApp.
//        id sharedApplication = [NSApplication sharedApplication];
//
//        id appDelegate = [MacOSAppDelegate alloc];
//        [sharedApplication setDelegate:appDelegate];
//        [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];
//        [sharedApplication activateIgnoringOtherApps:YES];
//
//        auto window = platform::MakeWindow<MyCustomWindow>(platform::WindowStyle{});
//
//        [sharedApplication run];
//
//    }
//    return 0;
//}
