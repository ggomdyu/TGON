#include "PrecompiledHeader.pch"

#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Platform/Window.h"
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
                windowStyle.width = 1000;
                windowStyle.height = 1000;
                windowStyle.showMiddle = true;
                windowStyle.caption = u8"Caption";
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
        GetRHI()->SetClearColor(math::Color4f(1.0f, 0.0f, 0.0f, 0.0f));
    }

    virtual void OnDidLaunch() override
    {
    }

    virtual void OnUpdate() override
    {
        GetRHI()->ClearColorBuffer();
        GetRHI()->Flush();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
