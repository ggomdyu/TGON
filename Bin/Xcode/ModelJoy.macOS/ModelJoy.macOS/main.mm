#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "Core/Platform/Window.h"
#include "Core/Utility/Delegate.h"
#include "Core/Utility/StaticIf.h"
#include "Core/Math/Color.h"
#include <boost/type_traits.hpp>
#include <iostream>

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

#include "Core/Object/Object.h"

class NewObject :
    public tgon::object::Object
{
public:
    TGON_MAKE_OBJECT_INTERFACE(NewObject);
};

template <typename _CharType>
struct TypeTraits
{
public:
    using CharType = _CharType;


};


template <class _CharType>
struct _LIBCPP_TYPE_VIS_ONLY ConstexprCharTraits
{
/* @section Ctor/Dtor */
public:
    using CharType = _CharType;

/* @section Public method */
public:
    constexpr static std::size_t Find(const _CharType* srcStr, std::size_t srcStrLength, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLength)
    {
        if ((srcStrOffset > srcStrLength) || ((srcStrLength - srcStrOffset) < srcFindSubStrLength))
        {
            return NPos;
        }

        if (srcFindSubStrLength == 0)
        {
            return srcStrOffset;
        }

        const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLength, srcFindSubStr, srcFindSubStr + srcFindSubStrLength);
        if (foundStr == srcStr + srcStrLength)
        {
            return NPos;
        }

        return static_cast<std::size_t>(foundStr - srcStr);
    }

    template <typename _CharType>
    constexpr int32_t Compare(const _CharType* lhsStr, std::size_t lhsStrLength, const _CharType* rhsStr, std::size_t rhsStrLength)
    {
        auto minSize = lhsStrLength < rhsStrLength ? lhsStrLength : rhsStrLength;

        auto ans = std::char_traits<_CharType>::compare(lhsStr, rhsStr, minSize);
        if (ans != 0)
        {
            return ans;
        }

        if (lhsStrLength < rhsStrLength)
        {
            return -1;
        }
        if (lhsStrLength > rhsStrLength)
        {
            return 1;
        }
        
        return 0;
    }

};


int main(int argc, char* argv[])
{
    std::char_traits<char> trait;

    @autoreleasepool
    {
        using namespace tgon;

        //constexpr string::FixedString32 fs = "23423f";
        auto hashV = hash::x65599Hash("123345");

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
