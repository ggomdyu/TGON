/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "Game/Engine/GameScene.h"

namespace tgon
{

class TGON_API IntroScene :
    public GameScene
{
public:
    TGON_DECLARE_RTTI(IntroScene);
    
private:
    
    float camZ;
public:
    IntroScene()
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();
        
        auto rootWindowSize = application->GetRootWindow().GetSize();
        
        m_graphicsModule = engine->FindModule<GraphicsModule>();
        m_inputModule = engine->FindModule<InputModule>();
        m_timeModule = engine->FindModule<TimeModule>();
        
        m_graphicsModule->GetGraphics().DisableDepthTest();
        m_graphicsModule->GetGraphics().EnableBlend();
        m_graphicsModule->GetGraphics().SetBlendMode(BlendMode::Alpha);
        
        // 카메라 생성
        {
            auto cameraObject = std::make_shared<GameObject>("camera1");
            const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
            camZ = 50.0f;
//            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
            this->AddObject(cameraObject);
        }
        
//        for (int i = 0; i < 25; ++i)
//        {
//            this->AddObject(std::make_shared<Firefly>(StringTraits<char>::Format("firefly_%d", i).first));
//        }
        
        // Intro에 사용할 Sprite 생성
        {
            auto fadeInObject = std::make_shared<GameObject>("fadeIn");
            fadeInObject->SetScale({8.38f, 4.42f, 1.0f});
            fadeInObject->SetPosition({0.0f, 0.0f, 10.0f});
            m_fadeInSpriteComponent = fadeInObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_fadeInSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f});
            m_fadeInSpriteComponent->SetOpacity(1.0f);
            this->AddObject(fadeInObject);
        }
        
        // Intro에 사용할 Sprite 생성
        {
            m_nightSkyObject = std::make_shared<GameObject>("nightSky");
            m_nightSkySpriteComponent = m_nightSkyObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/IntroScene/nightSky.png");
            float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
            m_nightSkyObject->SetScale({25.14f, 4.42f, 1.0f});
            //m_nightSkyObject->GetTransform().SetPosition({static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01 * 0.5f, 0.0f, 0.0f});
            this->AddObject(m_nightSkyObject);
        }

        SuperType::Update();
    }
    
public:
    virtual void Update() override
    {
        SuperType::Update();
        
        if (m_fadeInSpriteComponent->GetOpacity() >= 0.0f)
        {
            m_fadeInSpriteComponent->GetOpacity() -= 0.025f * m_timeModule->GetTickTime();
        }
        
        decltype(auto) keyboard = m_inputModule->GetKeyboard();
        if (keyboard->IsKeyHold(KeyCode::W))
        {
            camZ -= 0.05f;
            
            auto& camera = m_cameraComponent->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, camZ});
        }
        if (keyboard->IsKeyHold(KeyCode::S))
        {
            camZ += 0.05f;
            
            auto& camera = m_cameraComponent->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, camZ});
        }
        
        if (keyboard->IsKeyHold(KeyCode::Q))
        {
            m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, -0.05f});
        }
        if (keyboard->IsKeyHold(KeyCode::A))
        {
            m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, 0.05f});
        }

        // Move NightSky
        {
            auto rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
            float nightSkyImageLeftTopX = static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01f * 0.5f;
            if (m_nightSkyObject->GetPosition().x <= -nightSkyImageLeftTopX)
            {
                m_nightSkyObject->SetPosition({nightSkyImageLeftTopX, 0.0f, 0.0f});
            }
            else
            {
                m_nightSkyObject->Move({-1.0f * m_timeModule->GetTickTime(), 0.0f, 0.0f});
            }
        }
    }
    
private:
    std::shared_ptr<GraphicsModule> m_graphicsModule;
    std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
    std::shared_ptr<GameObject> m_nightSkyObject;
    std::shared_ptr<CameraComponent> m_cameraComponent;
    std::shared_ptr<SpriteRendererComponent> m_fadeInSpriteComponent;
    std::shared_ptr<SpriteRendererComponent> m_nightSkySpriteComponent;
};

} /* namespace tgon */
