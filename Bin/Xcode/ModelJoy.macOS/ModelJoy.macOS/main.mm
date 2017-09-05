#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <boost/type_traits.hpp>
#import <iostream>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>

#import "Core/Platform/Window.h"
#import "Core/Platform/Time.h"
#import "Core/Utility/Delegate.h"
#import "Core/Utility/StaticIf.h"
#import "Core/String/FixedString.h"
#import "Core/Math/Color.h"
#import "Core/Math/Math.h"
#import "Core/Object/ObjectUtility.h"

using tgon::platform::Window;

class MyCustomWindow :
    public Window
{
public:
    using Window::Window;

public:
    virtual void OnResize(int32_t width, int32_t height) override
    {
        std::cout << width << " " << height << std::endl;
    }
};

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        using namespace tgon;
        using namespace tgon::object;

        id sharedApplication = [NSApplication sharedApplication];

        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        auto window = platform::MakeWindow<MyCustomWindow>(platform::WindowStyle{});

        [NSApp activateIgnoringOtherApps:YES];
        [NSApp run];
    }

    return 0;
}
