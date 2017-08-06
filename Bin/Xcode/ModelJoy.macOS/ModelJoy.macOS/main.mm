#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <boost/type_traits.hpp>
#import <iostream>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>

#import "Core/Platform/Window.h"
#import "Core/Utility/Delegate.h"
#import "Core/Utility/StaticIf.h"
#import "Core/Math/Color.h"
#import "Core/Object/Object.h"

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

class NewObject :
    public tgon::object::Object
{
public:
    TGON_MAKE_OBJECT_INTERFACE(NewObject);
};

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        using namespace tgon;

        string::FixedString64 fs = "2342";
        fs.Find("223");


        //id sharedApplica.rtion = [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        id applicationName = [[NSProcessInfo processInfo] processName];

        auto window = platform::MakeWindow<platform::Window>(platform::WindowStyle{});

        // error...
//        NewObject* newObject = new NewObject;
//        const char* typeName = newObject->GetTypeName();
//        std::size_t hashCode = newObject->GetTypeHashCode();
//
//        tgon::object::Object* newObject2 = new NewObject;
//        const char* typeName2 = newObject2->GetTypeName();
//        std::size_t hashCode2 = newObject2->GetTypeHashCode();

//        constexpr auto typeInfo = NewObject::GetTypeInfo();

        //std::cout << typeName << std::endl;

       // std::size_t hashCode = newObject.GetTypeHashCode();

//        decltype(auto) typeName = NewObject::GetTypeInfo().GetTypeName().CStr();
//        decltype(auto) hashCode = NewObject::GetTypeInfo().GetHashCode();

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
