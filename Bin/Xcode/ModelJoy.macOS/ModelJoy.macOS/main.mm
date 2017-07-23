#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

void OnDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    {
        glVertex2f(0.0, 0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
    }
    glEnd();
    glFlush();
}

void OnHandleInput(unsigned char key, int x, int y)
{
}

void foo()
{

}

class SomeClass
{
public:
    void foo(){};
};

#include "Core/Platform/Window.h"
#include "Core/Utility/Delegate.h"
#include "Core/Utility/StaticIf.h"
#include <boost/type_traits.hpp>
#include <iostream>

using namespace tgon;
using namespace tgon::utility;

template <typename>
struct DelegateBinder;

template <typename _ReturnType, typename... _Args>
class DelegateBinder<_ReturnType(_Args...)>
{
public:
    template <_ReturnType(*Handler)(_Args...)>
    Delegate<void()> Bind(_ReturnType(*handler)(_Args...))
    {
        return Delegate<void()>::MakeDelegate<Handler>();
    }
};

class DelegateBinder2
{
public:
    template <typename Lambda>
    static Delegate<void()> Bind(Lambda lambda)
    {
        return Delegate<void()>::MakeDelegate(lambda);
    }
};

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        //id sharedApplication = [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        id applicationName = [[NSProcessInfo processInfo] processName];

        platform::WindowStyle windowStyle;
        windowStyle.caption = "hell존나덥다!!";
        windowStyle.x = 100;
        windowStyle.y = 20;
        windowStyle.width = 300;
        windowStyle.height = 300;
        //windowStyle.showMiddle = true;

        platform::Window window(windowStyle);

        char caption[256] {};
        window.GetCaptionTitle(caption);

        auto d1 = TGON_MAKE_DELEGATE(&foo);
        auto d2 = TGON_MAKE_DELEGATE([](){});
        auto d3 = TGON_MAKE_DELEGATE(&SomeClass::foo, nullptr);

        




        [NSApp activateIgnoringOtherApps:YES];
        [NSApp run];
    }

//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
//    foo();
//    glutInitWindowSize(300, 300);
//    glutCreateWindow("Hello world!");
//
//    glutKeyboardFunc(OnHandleInput);
//    glutDisplayFunc(OnDraw);
//    glutMainLoop();

    return 0;
}
