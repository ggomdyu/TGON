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
                windowStyle.title = u8"こんにちはHallo你好안녕하세요नमस्ते";
                windowStyle.enableSystemButton = true;
                windowStyle.hasCaption = true;
                windowStyle.resizeable = false;
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
    }
    
    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
