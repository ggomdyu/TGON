#include "PrecompiledHeader.h"

#include "TGON.h"
#include "TitleScene.h"

using namespace tgon;

class FireFly :
    public GameObject
{
public:
    TGON_DECLARE_RTTI(FireFly)

/**@section Constructor */
public:
    explicit FireFly(const StringHash& name);

/**@section Method */
public:
    void Initialize();
    virtual void Update() override;
    void Reset();

/**@section Variable */
private:
    bool m_canAdjustOpacity;
    bool m_needToIncreaseOpacity;
    float m_opacityAdjustSpeed;
    float m_moveSpeed;
    std::shared_ptr<UISprite> m_sprite;
};

FireFly::FireFly(const StringHash& name) :
    GameObject(name),
    m_canAdjustOpacity((Random().Next(0, 2) == 0) ? true : false),
    m_needToIncreaseOpacity(Random().Next(0, 1) == 0),
    m_opacityAdjustSpeed(static_cast<float>(Random().NextDouble(0.1, 0.4))),
    m_moveSpeed(static_cast<float>(Random().NextDouble(30, 60)))
{
}

void FireFly::Initialize()
{
    auto windowSize = Application::GetRootWindow()->GetExtent();
    auto transform = this->GetComponent<Transform>();
    auto scale = static_cast<float>(Random().NextDouble(0.3, 1.0));
    transform->SetLocalScale(Vector3(scale, scale, 1.0f));
    transform->SetLocalPosition(Vector3(static_cast<float>(Random().NextDouble(-windowSize.width / 2, windowSize.width / 2)), static_cast<float>(Random().NextDouble(-windowSize.height / 2 - 80.0f, windowSize.height / 2)), 0.0f));

    auto texture = std::make_shared<Texture>(u8"../../Resource/Objects/TitleScene/Firefly.png", FilterMode::Bilinear, WrapMode::Repeat, true, false);
    auto sprite = std::make_shared<UISprite>(texture);
    sprite->SetBlendColor(Color4f(1.0f, 1.0f, 1.0f, static_cast<float>(Random().NextDouble(0.4, 1.0))));
    auto spriteRendererComponent = this->AddComponent<SpriteRendererComponent>(sprite);
    m_sprite = spriteRendererComponent->GetSprite();
}

void FireFly::Reset()
{   
    m_sprite->SetBlendColor(Color4f(1.0f, 1.0f, 1.0f, static_cast<float>(Random().NextDouble(0.4, 1.0))));

    m_canAdjustOpacity = (Random().Next(0, 2) == 0) ? true : false;
    m_opacityAdjustSpeed = static_cast<float>(Random().NextDouble(0.0625, 0.25));
    m_moveSpeed = static_cast<float>(Random().NextDouble(30, 60));

    auto windowSize = Application::GetRootWindow()->GetExtent();
    auto transform = this->GetComponent<Transform>();
    auto scale = static_cast<float>(Random().NextDouble(0.3, 1.0));
    transform->SetLocalScale(Vector3(scale, scale, 1.0f));
    transform->SetLocalPosition(Vector3(static_cast<float>(Random().NextDouble(-windowSize.width / 2, windowSize.width / 2)), -windowSize.height / 2 - m_sprite->GetTexture()->GetSize().height / 2, 0.0f));
}

void FireFly::Update()
{
    SuperType::Update();

    auto tickTime = Application::GetEngine()->FindModule<TimeModule>()->GetTickTime();

    auto windowSize = Application::GetRootWindow()->GetExtent();
    auto transform = this->GetComponent<Transform>();
    auto newPos = transform->GetLocalPosition();
    if (newPos.y >= windowSize.height / 2 + 123.0F)
    {
        Reset();
    }
    else
    {
        newPos.y += m_moveSpeed * tickTime;
        transform->SetLocalPosition(newPos);
    }

    if (m_canAdjustOpacity)
    {
        float alpha = m_sprite->GetBlendColor().a;
        if (alpha >= 1.0f)
        {
            m_needToIncreaseOpacity = false;
        }
        else if (alpha <= 0.0f)
        {
            m_needToIncreaseOpacity = true;
        }

        alpha = (m_needToIncreaseOpacity) ? alpha + m_opacityAdjustSpeed * tickTime : alpha - m_opacityAdjustSpeed * tickTime;
        m_sprite->SetBlendColor(Color4f(1.0f, 1.0f, 1.0f, alpha));
    }
}

TitleScene::TitleScene()
{
    this->Initialize();
}

void TitleScene::Update()
{
    SuperType::Update();

    this->OnHandleInput();

    auto windowSize = Application::GetRootWindow()->GetExtent();
    float halfWindowWidth = windowSize.width * 0.5f;
    float halfWindowHeight = windowSize.height * 0.5f;
    auto nightSkyNewPos = m_nightSky->GetTransform()->GetLocalPosition();
    if (nightSkyNewPos.x <= -halfWindowWidth + -419.0f)
    {
        nightSkyNewPos = Vector3(-halfWindowWidth + 1257.0f, halfWindowHeight - 221.0f, 0.0f);
    }

    nightSkyNewPos.x -= 55.0f * m_timeModule->GetTickTime();
    m_nightSky->GetTransform()->SetLocalPosition(nightSkyNewPos);

    auto blendColor = m_fadeInSprite->GetBlendColor();
    blendColor.a -= 1.0f * m_timeModule->GetTickTime();
    m_fadeInSprite->SetBlendColor(blendColor);
}

void TitleScene::Initialize()
{
    m_inputModule = Application::GetEngine()->FindModule<InputModule>();
    m_timeModule = Application::GetEngine()->FindModule<TimeModule>();
    
    this->InitializeGraphics();
    this->CreateGameObjects();
}

void TitleScene::InitializeGraphics()
{
    auto engine = Application::GetInstance().GetEngine();
    
    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();
}

void TitleScene::CreateFontObjects()
{
    /*FontFactory ff;
    auto fontPath = Environment::GetFolderPath(Environment::SpecialFolder::Desktop).value() + "/Temporary/Thousand Party/Resource/Fonts/malgun.ttf";
    std::shared_ptr<Font> font = ff.CreateFont(fontPath.c_str());
    auto object = std::make_shared<GameObject>( "font", new Transform() );
    object->GetTransform()->SetLocalScale( { 1.0f, 1.0f, 1.0f } );
    object->GetTransform()->SetLocalPosition( Vector3( 0.0f, 0.0f, 0.0f ) );
    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();

    const wchar_t chArray[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvrwxyz가나다라마바사아자차카타파하";
    static auto textureAtlas = TextureAtlas::Create(I32Extent2D(512, 512), PixelFormat::RGBA8888, 6);
    for (auto ch : chArray)
    {
        const auto& glyphData = font->GetGlyphData(ch, 35);
        textureAtlas.Insert(glyphData.ch, ImageView(glyphData.bitmap.get(), glyphData.metrics.size, PixelFormat::RGBA8888));
    }

    auto& imageRect = textureAtlas.GetTextureRect(u'A');
    decltype(auto) texture = textureAtlas.GetAtlasTexture();
    decltype(auto) sprite = std::make_shared<UISprite>(texture);
    sprite->SetTextureRect(FRect(imageRect.x, imageRect.y, imageRect.width, imageRect.height));
    spriteComponent->SetSprite(sprite);
    this->AddObject( object );*/
//    static TextureAtlas textureAtlas(I32Extent2D(512, 512), PixelFormat::RGBA8888, 6);
//
//    float accumulatedXPos = -100.0f;
//    float accumulatedYPos = 0.0f;
//    const wchar_t str[] = L"";
//    for (int i = 0; i < std::extent<decltype(str)>::value - 1; ++i)
//    {
//       int32_t fontSize = 30;
//       auto& glyphData = font->GetGlyphData(str[i], fontSize);
//
//       if (i != 0)
//       {
//           auto& prevGlyphData = font->GetGlyphData( str[i - 1], fontSize );
//           accumulatedXPos -= (prevGlyphData.metrics.size.width - glyphData.metrics.size.width) / 2;
//
//           auto kerning = font->GetKerning( str[i - 1], str[i], fontSize );
//           accumulatedXPos += kerning.x;
//       }
//
//       float xPos = accumulatedXPos + glyphData.metrics.bearing.x;
//       float yPos = accumulatedYPos - glyphData.metrics.size.height / 2 + glyphData.metrics.bearing.y;
//
//       auto object = std::make_shared<GameObject>("introSprite1", new Transform());
//       object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
//       object->GetTransform()->SetLocalPosition(Vector3( xPos, yPos, 0.0f ));
//       auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
//       auto texture = std::make_shared<Texture>(&glyphData.bitmap[0], glyphData.metrics.size, PixelFormat::RGBA8888, FilterMode::Point, WrapMode::Clamp, false, false);
//       spriteComponent->SetSprite(std::make_shared<UISprite>(texture));
//
//       this->AddObject(object);
//
//       accumulatedXPos += glyphData.metrics.advance.x;
//    }
}

void TitleScene::CreateUIObjects()
{
    auto windowSize = Application::GetRootWindow()->GetExtent();
    float halfWindowWidth = windowSize.width * 0.5f;
    float halfWindowHeight = windowSize.height * 0.5f;

    const char* texturePathList[] =
    {
        u8"../../Resource/Backgrounds/TitleScene/nightSky.png",
        u8"../../Resource/Backgrounds/TitleScene/star.png",
        u8"../../Resource/Backgrounds/TitleScene/earth.png",
        u8"../../Resource/Backgrounds/TitleScene/girl.png",
        u8"../../Resource/UI/TitleScene/Logo.png",
        //u8"../../Resource/UI/TitleScene/Press.png",
        u8"../../Resource/UI/Common/FadeInOut.png",
    };
    Vector3 texturePosList[] =
    {
        Vector3(-halfWindowWidth + 1257.0f, halfWindowHeight - 221.0f, 0.0f),
        Vector3(-halfWindowWidth + 640.0f, halfWindowHeight - 360.0f, 0.0f),
        Vector3(-halfWindowWidth + 612.0f, halfWindowHeight - 388.0f, 0.0f),
        Vector3(-halfWindowWidth + 640.0f, halfWindowHeight - 221.0f, 0.0f),
        Vector3(-halfWindowWidth + 172.5f, halfWindowHeight - 92.5f, 0.0f),
        //Vector3(23.0f, 355.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
    };

    for (int i = 0; i < std::extent_v<decltype(texturePathList)>; ++i)
    {
        auto texture = std::make_shared<Texture>(texturePathList[i], FilterMode::Bilinear, WrapMode::Repeat, true, false);
        auto objectName = StringHash(*Path::GetFileNameWithoutExtension(texturePathList[i]));
        auto object = std::make_shared<GameObject>(objectName);
        object->GetTransform()->SetLocalPosition(texturePosList[i]);
        auto spriteComponent = object->AddComponent<SpriteRendererComponent>(std::make_shared<UISprite>(texture));
        this->AddObject(object);
    }

    auto fadeInObject = this->FindObject("FadeInOut");
    m_fadeInSprite = fadeInObject->GetComponent<SpriteRendererComponent>()->GetSprite();

    m_nightSky = this->FindObject("nightSky");
}

void TitleScene::CreateFireFlyObjects()
{
    for (int i = 0; i < 20; ++i)
    {
        auto fireFly = std::make_shared<FireFly>(StringHash(std::to_string(i)));
        fireFly->Initialize();
        this->AddObject(std::move(fireFly));
    }
}

void TitleScene::CreateGameObjects()
{
    this->CreateFontObjects();
    this->CreateUIObjects();
    this->CreateFireFlyObjects();
}

void TitleScene::OnHandleInput()
{
    /*auto moveableObject = this->FindObject("introSprite2");
    if (moveableObject == nullptr)
    {
        return;
    }

    auto transform = moveableObject->GetTransform();
    auto newPos = transform->GetLocalPosition();
    float speed = 200.0f;

    decltype(auto) keyboard = m_inputModule->GetKeyboard();
    if (keyboard->IsKeyHold(KeyCode::LeftArrow))
    {
        newPos.x -= speed * m_timeModule->GetTickTime();
    }
    if (keyboard->IsKeyHold(KeyCode::RightArrow))
    {
        newPos.x += speed * m_timeModule->GetTickTime();
    }
    if (keyboard->IsKeyHold(KeyCode::UpArrow))
    {
        newPos.y += speed * m_timeModule->GetTickTime();
    }
    if (keyboard->IsKeyHold(KeyCode::DownArrow))
    {
        newPos.y -= speed * m_timeModule->GetTickTime();
    }

    transform->SetLocalPosition(newPos);*/
}