#include "PrecompiledHeader.h"

#include "TGON.h"
#include "LogoScene.h"

using namespace tgon;

LogoScene::LogoScene()
{
    this->Initialize();
}

void LogoScene::Update()
{
    SuperType::Update();

    //object2->GetTransform()->SetLocalRotation({RandRange(-3.14f, 3.14f), RandRange(-3.14f, 3.14f), RandRange(-3.14f, 3.14f)});
    
    this->OnHandleInput();

//    auto elapsedTime = GetTickCount() - m_beginTime;
//    if (elapsedTime >= 8500)
//    {
//        auto gameSceneModule = Application::GetInstance()->GetEngine()->FindModule<GameSceneModule>();
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

void LogoScene::Initialize()
{
    m_inputModule = Application::GetEngine()->FindModule<InputModule>();
    
    this->InitializeGraphics();
    this->CreateGameObjects();
}

void LogoScene::InitializeGraphics()
{
    auto engine = Application::GetInstance().GetEngine();
    
    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();
}

void LogoScene::CreateCameraObject()
{
    auto camera = std::make_shared<GameObject>("camera1", new Transform());
    
    auto rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
    float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    camera->AddComponent<CameraComponent>(FRect(-halfWidth, -halfHeight, rootWindowSize.width, rootWindowSize.height), -1.0f, 1024.0f);
    this->AddGlobalObject(camera);
}

void LogoScene::CreateFontObject()
{
    FontFactory ff;
    auto fontPath = Environment::GetFolderPath(Environment::SpecialFolder::Desktop).value() + "/maplestory_bold.ttf";
    std::shared_ptr<Font> font = ff.CreateFont(fontPath.c_str());
//    auto object = std::make_shared<GameObject>( "font", new Transform() );
//    object->GetTransform()->SetLocalScale( { 1.0f, 1.0f, 1.0f } );
//    object->GetTransform()->SetLocalPosition( Vector3( 0.0f, 0.0f, 0.0f ) );
//    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
//
//    const wchar_t chArray[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvrwxyz가나다라마바사아자차카타파하";
//    static TextureAtlas textureAtlas(I32Extent2D(512, 512), PixelFormat::RGBA8888, 6);
//    //for (auto ch : chArray)
//    {
//        const auto& glyphData = font->GetGlyphData('A', 35);
//        const auto& glyphData2 = font->GetGlyphData('B', 35);
//        textureAtlas.Insert(glyphData.ch, ImageView(glyphData.bitmap.get(), glyphData.metrics.size, PixelFormat::RGBA8888));
//    }
//
//    auto& imageRect = textureAtlas.GetTextureRect(u'A');
//    decltype(auto) texture = textureAtlas.GetAtlasTexture();
//    decltype(auto) sprite = std::make_shared<UISprite>(texture);
//    sprite->SetTextureRect(FRect(imageRect.x, imageRect.y, imageRect.width, imageRect.height));
//    spriteComponent->SetSprite(sprite);
//    this->AddObject( object );
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

void LogoScene::CreateGameObjects()
{
    this->CreateCameraObject();
    this->CreateFontObject();
    
    auto desktopPath = *Environment::GetFolderPath(Environment::SpecialFolder::Desktop);

    auto object = std::make_shared<GameObject>("introSprite1", new Transform());
    object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
    auto texture = std::make_shared<Texture>(desktopPath + "/2.jpg", FilterMode::Bilinear, WrapMode::Repeat, true, false);
    spriteComponent->SetSprite(std::make_shared<UISprite>(texture));
    this->AddObject(object);
}

void LogoScene::OnHandleInput()
{
     decltype(auto) keyboard = m_inputModule->GetKeyboard();
     if (keyboard->IsKeyDown(KeyCode::Space) || keyboard->IsKeyDown(KeyCode::Return))
     {
//         auto currTime = GetTickCount();
//         auto elapsedTime = currTime - m_beginTime;
//         if (elapsedTime <= 1000)
//         {
//             m_beginTime = currTime - 1000.0f;
//         }
//         else if (elapsedTime <= 3500)
//         {
//             m_beginTime = currTime - 3500.0f;
//         }
//         else if (elapsedTime <= 5000)
//         {
//             m_beginTime = currTime - 5000.0f;
//         }
//         else if (elapsedTime <= 7500)
//         {
//             m_beginTime = currTime - 7500.0f;
//         }
     }
}
