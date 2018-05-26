#include "PrecompiledHeader.h"

#define TGON_USING_OPENGL 1
#include "Core/Utility/StaticInvoke.h"
#include "Core/Audio/AudioBuffer.h"
#include "Core/Audio/AudioPlayer.h"
#include "Core/Random/Random.h"
#include "Core/Object/Object.h"
#include "Core/Object/IRuntimeObjectUtility.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Generic/GenericWindowType.h"
#include "Core/File/Path.h"
#include "Core/Random/Random.h"
#include "Core/Drawing/Image.h"
#include "Core/Debug/Log.h"
#include "Core/Platform/Application.h"
#include "Core/Platform/Screen.h"
#include "Core/Platform/Locale.h"
#include "Core/Platform/ScreenType.h"
#include "Core/String/FixedString.h"
#include "Core/String/FixedStringUtility.h"
#include "Core/File/Path.h"
#include "Core/Utility/InstantiateCounter.h"
#include "Core/Math/Mathematics.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Extent.h"
#include "Core/Hash/UUID.h"
#include "Core/Hash/Hash.h"
#include "Core/Random/Random.h"
#include "Core/Utility/RAII.h"
#include "Core/File/Path.h"
#include "Core/Utility/Stopwatch.h"
#include "Core/Utility/Algorithm.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphicsType.h"
#include "Graphics/LowLevelRender/Generic/GenericGraphics.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShader.h"
#include "Graphics/LowLevelRender/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Render/Renderer.h"
#include "Graphics/Render/MeshUtility.h"
#include "Graphics/LowLevelRender/VertexBuffer.h"
#include "Graphics/LowLevelRender/IndexBuffer.h"
#include "Graphics/Render/FVF.h"
#include "Game/Object/Module/GraphicsModule.h"
#include "Game/Object/Module/TimeModule.h"
#include "Game/Object/GameObject.h"
#include "Game/Object/Component.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Application
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

/* @section Public constructor */
public:
    ThousandParty() :
        Application(WindowStyle())
    {
        this->AddModule<TimeModule>();
        this->AddModule<GraphicsModule>();
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
    }

/* @section Public event handler */
public:
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