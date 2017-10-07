#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

#include "Core/Platform/Application.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Math/Math.h"
////

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <AppKit/NSOpenGL.h>
#include <AppKit/NSOpenGLView.h>
#include <AppKit/NSWindow.h>

#include "Graphics/OpenGL/MacOS/MacOSOpenGLView.h"

using namespace tgon;
using namespace tgon::platform;

class TGON_API ModelJoy :
    public platform::Application
{
private:
    MacOSOpenGLView* view;

public:
    ModelJoy() :
        platform::Application(MakeSharedWindow<Window>(WindowStyle{}))
    {
        string::FixedString32 str = "zzzzzzzzzzzzzzzzzzzzzzzzzzzz";
        str.Assign("wefiojwef");



        NSWindow* nativeWindow = (__bridge NSWindow*)GetMainWindow()->GetNativeWindow();
        view = [[MacOSOpenGLView alloc] init];
        [nativeWindow setContentView:view];

        CGLLockContext([[view openGLContext] CGLContextObj]);
        {
            GLuint VertexArrayID;
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
            };

            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        }
        CGLUnlockContext([[view openGLContext] CGLContextObj]);
    }

    virtual void OnTerminate() override
    {
    }

    virtual void OnUpdate() override
    {
    }

    GLuint m_vertexBuffer;

    virtual void OnDraw() override
    {
        [[view openGLContext] makeCurrentContext];

        // We draw on a secondary thread through the display link
        // When resizing the view, -reshape is called automatically on the main
        // thread. Add a mutex around to avoid the threads accessing the context
        // simultaneously when resizing
        CGLLockContext([[view openGLContext] CGLContextObj]);
        {
            // 버퍼의 첫번째 속성값(attribute) : 버텍스들
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glVertexAttribPointer(
                                  0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
                                  3,                  // 크기(size)
                                  GL_FLOAT,           // 타입(type)
                                  GL_FALSE,           // 정규화(normalized)?
                                  0,                  // 다음 요소 까지 간격(stride)
                                  (void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
                                  );
            // 삼각형 그리기!
            glDrawArrays(GL_TRIANGLES, 0, 3); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형
            glDisableVertexAttribArray(0);
        }
        glClearColor(0.0f,0.0f,0.0f,0.0f);

        CGLFlushDrawable([[view openGLContext] CGLContextObj]);
        CGLUnlockContext([[view openGLContext] CGLContextObj]);
    }
};

TGON_DECLARE_APPLICATION(ModelJoy)
