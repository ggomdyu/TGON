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
    TGON_OBJECT(NewObject);
};

class NewObject2 :
    public NewObject
{
public:
    TGON_OBJECT(NewObject2);
};

class NewObject3 :
    public NewObject2
{
public:
    TGON_OBJECT(NewObject3);
};

class NewObject4 :
    public NewObject2
{
public:
    TGON_OBJECT(NewObject4);

    virtual void foo()
    {
        constexpr int n = 32342;
        std::cout << n << std::endl;
        //std::cout << GetDynamicType().GetHashCode() << std::endl;
        //std::cout << SuperType::GetDynamicType().GetHashCode() << std::endl;
    }
};

void foo()
{

}

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        using namespace tgon;
        using namespace tgon::object;

//        NSApplicationDelegate a;
//        [[NSApplication sharedApplication] delegate];


        //id sharedApplica.rtion = [NSApplication sharedApplication];
//        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
//        id applicationName = [[NSProcessInfo processInfo] processName];

        Object* p = new NewObject4;

        uint64_t begin[5];
        uint64_t end[5];
        uint64_t begin2[5];
        uint64_t end2[5];
        for (int r = 0 ; r < 5; ++r)
        {
            begin[r] = platform::GetOSExecutionTime();
            for (int i = 0; i < 5000; ++i)
            {
                std::cout<<(typeid(NewObject2*).hash_code() == typeid(p).hash_code());
                std::cout<<(typeid(NewObject3*).hash_code() == typeid(p).hash_code());
                std::cout<<(typeid(NewObject4*).hash_code() == typeid(p).hash_code());
            }
            end[r] = platform::GetOSExecutionTime();
        }

        for (int r = 0 ; r < 5; ++r)
        {
            begin2[r] = platform::GetOSExecutionTime();
            for (int i = 0; i < 5000; ++i)
            {
                std::cout<<dynamic_cast<NewObject2*>(p);
                std::cout<<dynamic_cast<NewObject3*>(p);
                std::cout<<dynamic_cast<NewObject4*>(p);
            }
            end2[r] = platform::GetOSExecutionTime();
        }
std::cout << "////////////////" << std::endl;
        for (int r = 0 ; r < 5; ++r)
            std::cout << end[r] - begin[r] << std::endl;
        std::cout << "////////////////" << std::endl;
        for (int r = 0 ; r < 5; ++r)
            std::cout << end2[r] - begin2[r] << std::endl;
        std::cout << "////////////////" << std::endl;
        //p->GetDynamicTypeInfo()->GetSuperTypeInfo()->GetSuperTypeInfo();

//        auto s = platform::GetProcessExecutionTime();
//        std::cout << DynamicCast<NewObject2>(p) << std::endl;
//        std::cout << DynamicCast<NewObject3>(p) << std::endl;
//        std::cout << DynamicCast<NewObject4>(p) << std::endl;
//        auto e = platform::GetProcessExecutionTime();

        //p->foo();
//
        //std::cout << dynamic_cast<NewObject2*>(p) << std::endl;
//        std::cout << dynamic_cast<NewObject3*>(p) << std::endl;
//        std::cout << dynamic_cast<NewObject4*>(p) << std::endl;

        //std::cout << DynamicCast<int*>(p) << std::endl;

       // p->foo();

//
//        std::cout << p->GetStaticType().GetName() << std::endl;
//        std::cout << p->GetDynamicType().GetName() << std::endl;

        //object::DynamicCastHelper<NewObject2*>::DynamicCast(p);
//
//        std::cout << FastDynamicCaster<NewObject2*>::FastDynamicCast(p) << std::endl;

//        std::cout << FastDynamicCast<NewObject2>(p) << std::endl;
//        std::cout << FastDynamicCast<NewObject>(p) << std::endl;

//        auto window = platform::MakeWindow<platform::Window>(platform::WindowStyle{});
//
//
//        std::cout << math::Min(0, 1, 4, -2) << std::endl;
//        std::cout << math::Max(0, 1, 24, 5) << std::endl;
//
//        [NSApp activateIgnoringOtherApps:YES];
//        [NSApp run];
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
