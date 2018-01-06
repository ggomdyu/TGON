#include "PrecompiledHeader.pch"

#include "Game/Engine/GameApplication.h"

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
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Graphics/RHI/RHIType.h"
#include "Graphics/RHI/IDynamicRHI.h"
#include "Graphics/Render/Renderer.h"
#include "Game/Module/GraphicsModule.h"
#include "Game/Module/TimeModule.h"
#include <GL/glew.h>

using namespace tgon;

class TGON_API ThousandParty :
    public game::GameApplication
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

public:
    ThousandParty() :
        game::GameApplication([&]()
        {
            core::WindowStyle windowStyle;
            {
                windowStyle.width = 500;
                windowStyle.height = 500;
                windowStyle.showMiddle = true;
                windowStyle.title = u8"こんにちはHallo你好안녕नमस्ते";
                windowStyle.enableSystemButton = true;
                windowStyle.hasCaption = true;
                windowStyle.resizeable = true;
            }
            return windowStyle;
        }(),
        [&]()
        {
            graphics::VideoMode videoMode;
            {
                videoMode.graphicsSDK = graphics::GraphicsSDK::OpenGL4_0;
                videoMode.enableHardwareAccelerate = true;
                videoMode.enableMultiSampling = true;
                videoMode.enableDoubleBuffer = true;
            }
            return videoMode;
        }())
    {
    }

    virtual void OnWillLaunch() override
    {
        SuperType::OnWillLaunch();
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();

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

        FindModule<game::GraphicsModule>()->GetRHI()->SwapBuffer();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)