#include "PrecompiledHeader.h"

#include <deque>
#include <functional>
#include <atomic>
#include <thread>
#include "TGON.h"
#include "IntroScene.h"
#include "LogoScene.h"
#include "Thread/DispatchQueue.h"
#include "Drawing/FontFactory.h"

#include <ft2build.h>
#include FT_FREETYPE_H

std::shared_ptr<tgon::GameObject> object1;
std::shared_ptr<tgon::GameObject> object2;
std::shared_ptr<tgon::GameObject> object3;
std::shared_ptr<tgon::GameObject> object4;
std::shared_ptr<tgon::GameObject> object5;

LogoScene::LogoScene()
{
    using namespace tgon;

    FontFactory ff;
    //ff.ImportFont("E:/Users/ggomdyu/Desktop/maplestory.ttf");

    auto engine = Application::GetInstance()->GetEngine();

    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height) }, -1.0f, 1024.0f);

    this->AddGlobalObject(cameraObject);
    
    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    {
        auto texture = std::make_shared<Texture>(GetDesktopDirectory() + "/1.jpg", TextureFilterMode::Bilinear, TextureWrapMode::Repeat, true);
        object1 = std::make_shared<GameObject>("introSprite1", new Transform());
        object1->GetTransform()->SetLocalScale({ 0.3f, 1.0f, 1.0f });
        object1->GetTransform()->SetLocalPosition({ 100.0f, 0.0f, 0.0f });
        m_introSpriteComponent1 = object1->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent1->SetSprite(std::make_shared<CanvasSprite>(texture));
        
        auto texture2 = std::make_shared<Texture>(GetDesktopDirectory() + "/2.jpg", TextureFilterMode::Bilinear, TextureWrapMode::Repeat, true);
        object2 = std::make_shared<GameObject>("introSprite1", new Transform());
        object2->GetTransform()->SetLocalScale({ 0.3f, 1.0f, 1.0f });
        object2->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
        m_introSpriteComponent2 = object2->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent2->SetSprite(std::make_shared<CanvasSprite>(texture2));

        object3 = std::make_shared<GameObject>("introSprite1", new Transform());
        object3->GetTransform()->SetLocalScale({ 0.3f, 1.0f, 1.0f });
        object3->GetTransform()->SetLocalPosition({ 400.0f, -200.0f, 0.0f });
        m_introSpriteComponent3 = object3->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent3->SetSprite(std::make_shared<CanvasSprite>(texture2));

        object4 = std::make_shared<GameObject>("introSprite1", new Transform());
        object4->GetTransform()->SetLocalScale({ 0.3f, 1.0f, 1.0f });
        object4->GetTransform()->SetLocalPosition({ -150.0f, -150.0f, 0.0f });
        m_introSpriteComponent4 = object4->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent4->SetSprite(std::make_shared<CanvasSprite>(texture2));
        m_introSpriteComponent4 = object4->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent4->SetSprite(std::make_shared<CanvasSprite>(texture2));
        m_introSpriteComponent4 = object4->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent4->SetSprite(std::make_shared<CanvasSprite>(texture2));
        m_introSpriteComponent4 = object4->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent4->SetSprite(std::make_shared<CanvasSprite>(texture2));

        object5 = std::make_shared<GameObject>("introSprite1", new Transform());
        object5->GetTransform()->SetLocalScale({ 0.3f, 1.0f, 1.0f });
        object5->GetTransform()->SetLocalPosition({ 100.0f, 100.0f, 0.0f });
        m_introSpriteComponent5 = object5->AddComponent<CanvasSpriteRendererComponent>();
        m_introSpriteComponent5->SetSprite(std::make_shared<CanvasSprite>(texture2));

        
        this->AddObject(object1);
        this->AddObject(object2);
        this->AddObject(object3);
        this->AddObject(object4);
        this->AddObject(object5);
    }

    //
    //{
    //    auto introObject2 = std::make_shared<tgon::GameObject>("introSprite2");
    //    introObject2->SetScale({ 8.38f, 4.42f, 1.0f });
    //    m_introSpriteComponent2 = introObject2->AddComponent<tgon::SpriteRendererComponent>(tgon::GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
    //    m_introSpriteComponent2->SetBlendColor({ 1.0f, 1.0f, 1.0f });
    //    m_introSpriteComponent2->SetOpacity(0.0f);
    //    this->AddObject(introObject2);
    //}

    //// Intro에 사용할 Sprite 생성
    //{
    //    auto fadeOutObject = std::make_shared<tgon::GameObject>("fadeOut");
    //    fadeOutObject->SetScale({ 8.38f, 4.42f, 1.0f });
    //    m_fadeOutSpriteComponent = fadeOutObject->AddComponent<tgon::SpriteRendererComponent>(tgon::GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
    //    m_fadeOutSpriteComponent->SetBlendColor({ 0.0f, 0.0f, 0.0f });
    //    m_fadeOutSpriteComponent->SetOpacity(0.0f);
    //    this->AddObject(fadeOutObject);
    //}

    m_beginTime = tgon::GetTickCount();

    SuperType::Update();
}

void LogoScene::Update()
{
    SuperType::Update();

    
    //object2->GetTransform()->SetLocalRotation({tgon::RandRange(-3.14f, 3.14f), tgon::RandRange(-3.14f, 3.14f), tgon::RandRange(-3.14f, 3.14f)});
    
//    this->OnHandleInput();

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
