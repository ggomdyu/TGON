#include "PrecompiledHeader.h"

#include "TGON.h"
#include "IntroScene.h"

using namespace tgon;
//
//class TGON_API Firefly final :
//    public GameObject
//{
//public:
//    TGON_DECLARE_RTTI(Firefly)
//
//public:
//    Firefly(const StringHash& name) :
//        GameObject(name, nullptr)
//    {
//        Application& application = Application::GetInstance();
//
//        //m_fireflySpriteComponent = this->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "Assets/Image/IntroScene/firefly.png");
//        //m_fireflySpriteComponent->SetBlendColor({ 1.0f, 1.0f, 1.0f });
//
//        //this->SetScale({ 0.31f, 0.31f, 1.0f });
//
//        this->Reset();
//    }
//
//public:
//    virtual void Update() override
//    {
//        SuperType::Update();
//
//        //this->Move(Vector3(0.0f, 0.0f, m_speed * m_timeModule->GetTickTime()));
//
//        if (m_enableOpacityChange)
//        {
//            //float opacity = m_fireflySpriteComponent->GetBlendColor().a;
//
//            //if (opacity >= 1.0f)
//            //{
//            //    needToIncreaseOpacity = false;
//            //}
//            //else if (opacity <= 0)
//            //{
//            //    needToIncreaseOpacity = true;
//            //}
//
//            //if (needToIncreaseOpacity)
//            //{
//            //    m_fireflySpriteComponent->GetBlendColor().a += m_opacityChangeSpeed * m_timeModule->GetTickTime();
//            //}
//            //else
//            //{
//            //     m_fireflySpriteComponent->GetBlendColor().a -= m_opacityChangeSpeed * m_timeModule->GetTickTime();
//            //}
//        }
//    }
//
//private:
//    void Reset()
//    {
//        //m_fireflySpriteComponent->SetBlendColor({ 1.0f, 1.0f, 1.0f });
//
//        //this->SetScale({ 0.1f, 0.1f, 1.0f });
//
//        //            I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
//        //this->SetPosition({ RandRange(-0.5f, 0.5f), 0.0f, -3.0f });
//        //            RandRange(-rootWindowSize.width * 0.5f, rootWindowSize.width * 0.5f)
//        //            -rootWindowSize.height * 0.5f
//        m_enableOpacityChange = (Random().Next(0, 2) == 0) ? true : false;
//        m_opacityChangeSpeed = Random().NextDouble(0.00392, 0.01568);
//        m_speed = Random().Next(0.3f, 1.0f);
//    }
//
//private:
//    bool m_enableOpacityChange = false;
//    bool needToIncreaseOpacity = false;
//    float m_opacityChangeSpeed = 0.0f;
//    float m_speed = 0.0f;
//    std::shared_ptr<SpriteRendererComponent> m_fireflySpriteComponent;
//    std::shared_ptr<TimeModule> m_timeModule;
//};

IntroScene::IntroScene()
{
    decltype(auto) application = Application::GetInstance();
    decltype(auto) engine = application.GetEngine();
        
    auto rootWindowSize = application.GetRootWindow()->GetExtent();
        
    m_graphicsModule = engine->FindModule<GraphicsModule>();
    m_inputModule = engine->FindModule<InputModule>();
    m_timeModule = engine->FindModule<TimeModule>();
        
    m_graphicsModule->GetGraphics().DisableDepthTest();
    m_graphicsModule->GetGraphics().EnableBlend();
    m_graphicsModule->GetGraphics().SetBlendMode(BlendMode::Alpha);
        
    // 카메라 생성
//    {
//        auto cameraObject = std::make_shared<GameObject>("camera1");
//        const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
//        const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
//        const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
//        m_cameraComponent = cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
//        camZ = 50.0f;
////            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
//        this->AddObject(cameraObject);
//    }
//        
////        for (int i = 0; i < 25; ++i)
////        {
////            this->AddObject(std::make_shared<Firefly>(StringTraits<char>::Format("firefly_%d", i).first));
////        }
//        
//    // Intro에 사용할 Sprite 생성
//    {
//        auto fadeInObject = std::make_shared<GameObject>("fadeIn");
//        fadeInObject->SetScale({8.38f, 4.42f, 1.0f});
//        fadeInObject->SetPosition({0.0f, 0.0f, 10.0f});
//        m_fadeInSpriteComponent = fadeInObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
//        m_fadeInSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f});
//        m_fadeInSpriteComponent->SetOpacity(1.0f);
//        this->AddObject(fadeInObject);
//    }
//        
//    // Intro에 사용할 Sprite 생성
//    {
//        m_nightSkyObject = std::make_shared<GameObject>("nightSky");
//        m_nightSkySpriteComponent = m_nightSkyObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/IntroScene/nightSky.png");
//        float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
//        m_nightSkyObject->SetScale({25.14f, 4.42f, 1.0f});
//        //m_nightSkyObject->GetTransform().SetPosition({static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01 * 0.5f, 0.0f, 0.0f});
//        this->AddObject(m_nightSkyObject);
//    }

    SuperType::Update();
}
    
void IntroScene::Update()
{
    SuperType::Update();
        
    //if (m_fadeInSpriteComponent->GetOpacity() >= 0.0f)
    //{
    //    m_fadeInSpriteComponent->GetOpacity() -= 0.025f * m_timeModule->GetTickTime();
    //}
    //    
    //decltype(auto) keyboard = m_inputModule->GetKeyboard();
    //if (keyboard->IsKeyHold(tgon::KeyCode::W))
    //{
    //    camZ -= 0.05f;
    //        
    //    auto& camera = m_cameraComponent->GetCamera();
    //    camera->SetEyePt({0.0f, 0.0f, camZ});
    //}
    //if (keyboard->IsKeyHold(tgon::KeyCode::S))
    //{
    //    camZ += 0.05f;
    //        
    //    auto& camera = m_cameraComponent->GetCamera();
    //    camera->SetEyePt({0.0f, 0.0f, camZ});
    //}
    //    
    //if (keyboard->IsKeyHold(tgon::KeyCode::Q))
    //{
    //    m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, -0.05f});
    //}
    //if (keyboard->IsKeyHold(tgon::KeyCode::A))
    //{
    //    m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, 0.05f});
    //}

    //// Move NightSky
    //{
    //    auto rootWindowSize = Application::GetRootWindow().GetSize();
    //    float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
    //    float nightSkyImageLeftTopX = static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01f * 0.5f;
    //    if (m_nightSkyObject->GetPosition().x <= -nightSkyImageLeftTopX)
    //    {
    //        m_nightSkyObject->SetPosition({nightSkyImageLeftTopX, 0.0f, 0.0f});
    //    }
    //    else
    //    {
    //        m_nightSkyObject->Move({-1.0f * m_timeModule->GetTickTime(), 0.0f, 0.0f});
    //    }
    //}
}
