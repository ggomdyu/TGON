#include "PrecompiledHeader.h"

#include "TGON.h"
#include "LogoScene.h"
#include "TitleScene.h"

using namespace tgon;

LogoScene::LogoScene()
{
    this->Initialize();
}

void LogoScene::Update()
{
    SuperType::Update();
    
    this->OnHandleInput();

    auto elapsedTime = Environment::GetTickCount() - m_beginTime;
    if (elapsedTime >= 8500)
    {
        auto gameSceneModule = Application::GetEngine()->FindModule<SceneModule>();
        gameSceneModule->ChangeScene(new TitleScene);
    }
    else if (elapsedTime >= 7500)
    {
        {
            auto blendColor = m_logoImages[2]->GetBlendColor();
            if (blendColor.a <= 1.0f)
            {
                blendColor.a += 2.5f * m_timeModule->GetTickTime();
                m_logoImages[2]->SetBlendColor(blendColor);
            }
        }

        {
            auto blendColor = m_logoImages[1]->GetBlendColor();
            if (blendColor.a <= 1.0f)
            {
                blendColor.a += 2.0f * m_timeModule->GetTickTime();
                m_logoImages[1]->SetBlendColor(blendColor);
            }
        }
    }
    else if (elapsedTime >= 5000)
    {
        auto blendColor = m_logoImages[1]->GetBlendColor();
        if (blendColor.a <= 1.0f)
        {
            blendColor.a += 2.0f * m_timeModule->GetTickTime();
            m_logoImages[1]->SetBlendColor(blendColor);
        }
    }
    else if (elapsedTime >= 3500)
    {
        auto blendColor = m_logoImages[0]->GetBlendColor();
        if (blendColor.a >= 0.0f)
        {
            blendColor.a -= 2.0f * m_timeModule->GetTickTime();
            m_logoImages[0]->SetBlendColor(blendColor);
        }
    }
    else if (elapsedTime >= 1000)
    {
        auto blendColor = m_logoImages[0]->GetBlendColor();
        if (blendColor.a <= 1.0f)
        {
            blendColor.a += 2.0f * m_timeModule->GetTickTime();
            m_logoImages[0]->SetBlendColor(blendColor);
        }
    }
}

void LogoScene::Initialize()
{
    this->InitializeGraphics();
    this->CreateGameObjects();

    m_beginTime = Environment::GetTickCount();
    m_inputModule = Application::GetEngine()->FindModule<InputModule>();
    m_timeModule = Application::GetEngine()->FindModule<TimeModule>();
}

void LogoScene::InitializeGraphics()
{
    auto engine = Application::GetInstance().GetEngine();
    
    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();
}

void LogoScene::CreateCameraObject()
{
    auto camera = std::make_shared<GameObject>("camera1");
    
    auto rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
    float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    camera->AddComponent<CameraComponent>(FRect(-halfWidth, -halfHeight, rootWindowSize.width, rootWindowSize.height), -1.0f, 1024.0f);
    this->AddGlobalObject(camera);
}

void LogoScene::CreateUIObject()
{
    auto windowSize = Application::GetRootWindow()->GetExtent();
    float halfWindowWidth = windowSize.width * 0.5f;
    float halfWindowHeight = windowSize.height * 0.5f;

    const char* texturePathList[] =
    {
        u8"../../Resource/Backgrounds/IntroScene/Team_logo.png",
        u8"../../Resource/Backgrounds/IntroScene/ON_logo.png",
        u8"../../Resource/UI/Common/FadeInOut.png",
    };

    for (int i = 0; i < std::extent_v<decltype(texturePathList)>; ++i)
    {
        auto texture = std::make_shared<Texture>(texturePathList[i], FilterMode::Bilinear, WrapMode::Repeat, true, false);
        auto object = std::make_shared<GameObject>(StringHash(std::to_string(i)));
        auto sprite = std::make_shared<UISprite>(texture);
        sprite->SetBlendColor(Color4f(1.0f, 1.0f, 1.0f, 0.0f));
        auto spriteComponent = object->AddComponent<SpriteRendererComponent>(sprite);
        this->AddObject(object);

        m_logoImages[i] = sprite;
    }
}

void LogoScene::CreateGameObjects()
{
    this->CreateCameraObject();
    this->CreateUIObject();
}

void LogoScene::OnHandleInput()
{
    decltype(auto) keyboard = m_inputModule->GetKeyboard();
    if (keyboard->IsKeyDown(KeyCode::Space))
    {
        auto elapsedTime = Environment::GetTickCount() - m_beginTime;
        if (elapsedTime >= 7500)
        {
        }
        else if (elapsedTime >= 5000)
        {
            m_beginTime -= 7500 - elapsedTime;
        }
        else if (elapsedTime >= 3500)
        {
        }
        else if (elapsedTime >= 1000)
        {
            m_beginTime -= 3500 - elapsedTime;
        }
        else
        {
            m_beginTime -= 1000 - elapsedTime;
        }
    }
}
