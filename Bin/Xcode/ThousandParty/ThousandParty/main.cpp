#include "PrecompiledHeader.pch"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/WindowType.h"
#include "Core/Platform/Time.h"
#include "Core/Platform/Screen.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/String/StringView.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Utility/AutoCast.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Color.h"
#include "Graphics/RHI/Base/BaseRHIType.h"
#include "Graphics/RHI/OpenGL/OpenGLRHI.h"
#include "Game/Engine/GameApplication.h"
#include <opengl/GL.h>

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

    };

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

        float newX = std::sin(x += 0.0001);
        float newY = std::sin(y += 0.0001);

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