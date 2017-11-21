#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

#include "Graphics/Platform/GraphicsApplication.h"
#include "Graphics/RHI/OpenGL/OpenGLRHI.h"
#include "Core/Platform/Window.h"
#include "Core/Object/Object.h"
#include "Core/Platform/Time.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/AutoCast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"

#include <vector>
#include <AppKit/NSOpenGL.h>
#include <AppKit/NSOpenGLView.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <AppKit/NSWindow.h>
#include <limits>

void RotateZ(tgon::math::Vector3& v, float radian)
{
//    const float radCos = cosf(theta);
//    const float radSin = sinf(theta);
//
//    v.x *= radCos;
//    v.y *= -radSin;
}

using namespace tgon;

class TGON_API ThousandParty :
    public platform::GraphicsApplication
{
public:
    ThousandParty() :
        platform::GraphicsApplication([&]()
        {
            tgon::platform::WindowStyle wndStyle;
            {
                wndStyle.caption = u8"dfsfs";
                wndStyle.resizeable = false;
            }
            return wndStyle;
        }(),
        [&]()
        {
            rhi::VideoMode videoMode;
            {
                videoMode.graphicsSDK = rhi::GraphicsSDK::OpenGL;
                videoMode.viewWidth = 1000;
                videoMode.viewHeight = 600;
            }
            return videoMode;
        }())
    {
    }

    virtual void OnWillLaunch() override
    {
        NSWindow* nativeWindow = (__bridge NSWindow*)GetMainWindow()->GetNativeWindow();
        view = [[NSOpenGLView alloc] init];
        [nativeWindow setContentView:view];


        [[view openGLContext] makeCurrentContext];
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    virtual void OnDidLaunch() override
    {
    }

    virtual void OnUpdate() override
    {
    }

    virtual void OnDraw() override
    {
        [[view openGLContext] makeCurrentContext];

        // We draw on a secondary thread through the display link
        // When resizing the view, -reshape is called automatically on the main
        // thread. Add a mutex around to avoid the threads accessing the context
        // simultaneously when resizing
        CGLLockContext([[view openGLContext] CGLContextObj]);

        glClear(GL_COLOR_BUFFER_BIT);

        GetRHI()->BeginScene(rhi::PrimitiveType::TriangleList);
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.5, -0.5, -0.5);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0, 0.5, -0.5);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5, -0.5, -0.5);
        }
        {
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5, -0.5, -0.5);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0, 0.0, 0.5);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.5, -0.5, -0.5);
        }
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            static float alpha = 0.0f;
            glColor4f(1.0f, 0.0f, 0.0f, alpha);
            glVertex3f(0.0, 0.0, 0.5);
            glColor4f(0.0f, 1.0f, 0.0f, alpha);
            glVertex3f(0.5, -0.5, -0.5);
            glColor4f(0.0f, 0.0f, 1.0f, alpha);
            glVertex3f(0.0, 0.5, 0.5);

            alpha += 0.005f;
        }

        GetRHI()->EndScene();
        GetRHI()->Flush();

        CGLFlushDrawable([[view openGLContext] CGLContextObj]);
        CGLUnlockContext([[view openGLContext] CGLContextObj]);
    }

private:
    NSOpenGLView* view;
};

TGON_DECLARE_APPLICATION(ThousandParty)
