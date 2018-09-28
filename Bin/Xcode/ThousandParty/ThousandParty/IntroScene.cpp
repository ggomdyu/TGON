#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API Firefly final :
    public GameObject
{
public:
    TGON_DECLARE_RTTI(Firefly);

public:
    Firefly(const StringHash& name) :
        GameObject(name)
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();

        m_timeModule = engine->FindModule<TimeModule>();

        m_fireflySpriteComponent = this->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "Assets/Image/IntroScene/firefly.png");
        m_fireflySpriteComponent->SetBlendColor({ 1.0f, 1.0f, 1.0f });

        this->SetScale({ 0.31f, 0.31f, 1.0f });

        this->Reset();
    }

public:
    virtual void Update() override
    {
        SuperType::Update();

        this->Move(Vector3(0.0f, 0.0f, m_speed * m_timeModule->GetTickTime()));

        if (m_enableOpacityChange)
        {
            //float opacity = m_fireflySpriteComponent->GetBlendColor().a;

            //if (opacity >= 1.0f)
            //{
            //    needToIncreaseOpacity = false;
            //}
            //else if (opacity <= 0)
            //{
            //    needToIncreaseOpacity = true;
            //}

            //if (needToIncreaseOpacity)
            //{
            //    m_fireflySpriteComponent->GetBlendColor().a += m_opacityChangeSpeed * m_timeModule->GetTickTime();
            //}
            //else
            //{
            //     m_fireflySpriteComponent->GetBlendColor().a -= m_opacityChangeSpeed * m_timeModule->GetTickTime();
            //}
        }
    }

private:
    void Reset()
    {
        m_fireflySpriteComponent->SetBlendColor({ 1.0f, 1.0f, 1.0f });

        this->SetScale({ 0.1f, 0.1f, 1.0f });

        //            I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
        this->SetPosition({ RandRange(-0.5f, 0.5f), 0.0f, -3.0f });
        //            RandRange(-rootWindowSize.width * 0.5f, rootWindowSize.width * 0.5f)
        //            -rootWindowSize.height * 0.5f
        m_enableOpacityChange = (RandRange(0, 2) == 0) ? true : false;
        m_opacityChangeSpeed = RandRange(0.00392f, 0.01568f);
        m_speed = RandRange(0.3f, 1.0f);
    }

private:
    bool m_enableOpacityChange = false;
    bool needToIncreaseOpacity = false;
    float m_opacityChangeSpeed = 0.0f;
    float m_speed = 0.0f;
    std::shared_ptr<SpriteRendererComponent> m_fireflySpriteComponent;
    std::shared_ptr<TimeModule> m_timeModule;
};

