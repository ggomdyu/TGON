#include "PrecompiledHeader.pch"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/ApplicationType.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/WindowType.h"
#include "Core/Platform/Time.h"
#include "Core/Platform/Debug.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/AutoCast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"
#include "Core/Hash/UUID.h"
#include "Graphics/RHI/Base/BaseRHIType.h"
#include "Graphics/RHI/OpenGL/OpenGLRHI.h"
#include "Game/Engine/GameApplication.h"
#include <opengl/GL.h>
#include "Graphics/Render/OpenGL/Shader.h"
#include "Core/Utility/ExpressionTemplate.h"

class V
{
public:
    V(int a, int b, int c)
    {
        p[0] = a;
        p[1] = b;
        p[2] = c;
    }

    template <typename F, typename S>
    V(const tgon::utility::BaseExpression<F, S>& expr)
    {
        for (int i = 0; i < 3; ++i)
        {
            p[i] = expr[i];
        }
    }

    int& operator[](int index)
    {
        return p[index];
    }

    const int& operator[](int index) const
    {
        return p[index];
    }

    tgon::utility::PlusExpression<V, V> operator+(const V& rhs)
    {
        return {*this, rhs};
    }

private:
    int p[3];
};

using namespace tgon;
using namespace tgon::string;
using namespace tgon::platform;
using namespace tgon::engine;

class TGON_API ThousandParty :
    public engine::GameApplication
{
public:
    ThousandParty() :
        engine::GameApplication([&]()
        {
            platform::WindowStyle windowStyle;
            {
                windowStyle.width = 500;
                windowStyle.height = 500;
                windowStyle.showMiddle = true;
                windowStyle.title = u8"Hallo?";
                windowStyle.enableSystemButton = true;
            }
            return windowStyle;
        }(),
        [&]()
        {
            rhi::VideoMode videoMode;
            {
                videoMode.graphicsSDK = rhi::GraphicsSDK::OpenGL;
                videoMode.enableHardwareAccelerate = true;
                videoMode.enableMultiSampling = true;
                videoMode.enableDoubleBuffer = true;
            }
            return videoMode;
        }())
    {
        V v(1, 5 ,6);
        V v2(1, 53 ,6);

        auto v3 = v + v2 + v2;
        auto v4 = v3 + v3;

        V v5 = v4;

        int n = 3;
    }

    virtual void OnWillLaunch() override
    {
        GetRHI()->SetClearColor(math::Color4f(0.3f, 0.4f, 0.6f, 1.0f));
    }

    virtual void OnDidLaunch() override
    {
    }
    
    virtual void OnUpdate() override
    {
        static float x = 0.0f;
        static float y = 0.0f;

        float newX = std::sin(x += 0.01);
        float newY = std::sin(y += 0.01);

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0 + newX, 0.5 + newY);
        glVertex2f(-0.5 + newX, -0.5 + newY);
        glVertex2f(0.5 + newX, -0.5 + newY);
        glEnd();
        glFinish();

        GetRHI()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
