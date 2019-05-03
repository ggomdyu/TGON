#include "PrecompiledHeader.h"

#include "Core/Engine/Module/InputModule.h"
#include "Core/Engine/Module/TimeModule.h"
#include "Core/Platform/Application.h"
#include "Core/Time/Time.h"
#include "Core/Math/Mathematics.h"
#include "Core/File/Path.h"
#include "Core/Hardware/Keyboard.h"
#include "Graphics/Engine/GraphicsModule.h"
#include "Graphics/Render/Sprite.h"
#include "Graphics/LowLevel/Texture.h"
#include "Game/Object/Component/SpriteRendererComponent.h"
#include "Game/Object/Component/CameraComponent.h"
#include "Game/Engine/Module/GameSceneModule.h"

#include "IntroScene.h"
#include "LogoScene.h"

LogoScene::LogoScene()
{
    using namespace tgon;
    
    decltype(auto) application = Application::GetInstance();
    decltype(auto) engine = application->GetEngine();

    m_graphicsModule = engine->FindModule<GraphicsModule>();
    m_inputModule = engine->FindModule<InputModule>();
    m_timeModule = engine->FindModule<TimeModule>();

    m_graphicsModule->GetGraphics().DisableDepthTest();
    m_graphicsModule->GetGraphics().SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

    // 카메라 생성
    {
        auto cameraObject = std::make_shared<GameObject>("camera1");
        const tgon::I32Extent2D rootWindowSize = application->GetRootWindow()->GetSize();
        const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
        const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
        m_cameraComponent = cameraObject->AddComponent<CameraComponent>(tgon::FRect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
//        m_cameraComponent = cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
        this->AddObject(cameraObject);
    }

    //// Intro에 사용할 Sprite 생성

    {
        auto introObject1 = std::make_shared<GameObject>("introSprite1");
        introObject1->GetTransform().SetLocalScale({ 8.38f, 4.42f, 1.0f });
        m_introSpriteComponent1 = introObject1->AddComponent<SpriteRendererComponent>();
        m_introSpriteComponent1->SetSprite(std::make_shared<Sprite>(std::make_shared<Texture>(GetDesktopDirectory() + "/s.png" )));
//        m_introSpriteComponent1->SetBlendColor({ 1.0f, 1.0f, 1.0f });
//        m_introSpriteComponent1->SetOpacity(0.0f);
        this->AddObject(introObject1);
    }

    // Intro에 사용할 Sprite 생성
//    {
//        auto introObject2 = std::make_shared<tgon::GameObject>("introSprite2");
//        introObject2->SetScale({ 8.38f, 4.42f, 1.0f });
//        m_introSpriteComponent2 = introObject2->AddComponent<tgon::SpriteRendererComponent>(tgon::GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
//        m_introSpriteComponent2->SetBlendColor({ 1.0f, 1.0f, 1.0f });
//        m_introSpriteComponent2->SetOpacity(0.0f);
//        this->AddObject(introObject2);
//    }
//
//    // Intro에 사용할 Sprite 생성
//    {
//        auto fadeOutObject = std::make_shared<tgon::GameObject>("fadeOut");
//        fadeOutObject->SetScale({ 8.38f, 4.42f, 1.0f });
//        m_fadeOutSpriteComponent = fadeOutObject->AddComponent<tgon::SpriteRendererComponent>(tgon::GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
//        m_fadeOutSpriteComponent->SetBlendColor({ 0.0f, 0.0f, 0.0f });
//        m_fadeOutSpriteComponent->SetOpacity(0.0f);
//        this->AddObject(fadeOutObject);
//    }

    m_beginTime = tgon::GetTickCount();

    SuperType::Update();
}

void LogoScene::Update()
{
    SuperType::Update();

    this->OnHandleInput();

//    auto elapsedTime = tgon::GetTickCount() - m_beginTime;
//    if (elapsedTime >= 8500)
//    {
//        auto gameSceneModule = tgon::Application::GetInstance()->GetEngine()->FindModule<tgon::GameSceneModule>();
//
//        gameSceneModule->ChangeScene<IntroScene>();
//        return;
//    }
//    else if (elapsedTime >= 7500)
//    {
//        if (m_fadeOutSpriteComponent->GetOpacity() <= 1.0f)
//        {
//            m_fadeOutSpriteComponent->GetOpacity() += 2.5f * m_timeModule->GetTickTime();
//        }
//    }
//    else if (elapsedTime >= 5000)
//    {
//        if (m_introSpriteComponent2->GetOpacity() <= 1.0f)
//        {
//            m_introSpriteComponent2->GetOpacity() += 2.0f * m_timeModule->GetTickTime();
//        }
//    }
//    else if (elapsedTime >= 3500)
//    {
//        if (m_introSpriteComponent1->GetOpacity() >= 0.0f)
//        {
//            m_introSpriteComponent1->GetOpacity() -= 2.0f * m_timeModule->GetTickTime();
//        }
//    }
//    else if (elapsedTime >= 1000)
//    {
//        if (m_introSpriteComponent1->GetOpacity() <= 1.0f)
//        {
//            m_introSpriteComponent1->GetOpacity() += 2.0f * m_timeModule->GetTickTime();
//        }
//    }
}

void LogoScene::OnHandleInput()
{
    /* decltype(auto) keyboard = m_inputModule->GetKeyboard();
     if (keyboard->IsKeyDown(tgon::KeyCode::Space) || keyboard->IsKeyDown(tgon::KeyCode::Return))
     {
         auto currTime = tgon::GetTickCount();
         auto elapsedTime = currTime - m_beginTime;
         if (elapsedTime <= 1000)
         {
             m_beginTime = currTime - 1000.0f;
         }
         else if (elapsedTime <= 3500)
         {
             m_beginTime = currTime - 3500.0f;
         }
         else if (elapsedTime <= 5000)
         {
             m_beginTime = currTime - 5000.0f;
         }
         else if (elapsedTime <= 7500)
         {
             m_beginTime = currTime - 7500.0f;
         }
     }*/
}
