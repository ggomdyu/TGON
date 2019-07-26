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
#include "Graphics/TextureAtlas.h"
#include "String/UnicodeScalar.h"
#include "Time/TimeZoneInfo.h"

std::shared_ptr<tgon::GameObject> object1;
std::shared_ptr<tgon::GameObject> object2;
std::shared_ptr<tgon::GameObject> object3;
std::shared_ptr<tgon::GameObject> object4;
std::shared_ptr<tgon::GameObject> object5;

LogoScene::LogoScene()
{
    using namespace tgon;
    
    m_beginTime = tgon::GetTickCount();

    SuperType::Update();

    this->InitPhase4();
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

void LogoScene::InitPhase1()
{
    using namespace tgon;

    auto engine = Application::GetInstance()->GetEngine();

    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height) }, -1.0f, 1024.0f);
    this->AddGlobalObject(cameraObject);

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    auto texture = std::make_shared<Texture>(Path::GetDesktopDirectory() + "/2.jpg", FilterMode::Bilinear, WrapMode::Repeat, true, false);

    object1 = std::make_shared<GameObject>("introSprite1", new Transform());
    object1->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object1->GetTransform()->SetLocalPosition({ 100.0f, 0.0f, 0.0f });
    m_introSpriteComponent1 = object1->AddComponent<SpriteRendererComponent>(std::make_shared<Sprite>(texture));

    object2 = std::make_shared<GameObject>("introSprite1", new Transform());
    object2->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object2->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    m_introSpriteComponent2 = object2->AddComponent<SpriteRendererComponent>(std::make_shared<Sprite>(texture));

    this->AddObject(object1);
    this->AddObject(object2);
}

void LogoScene::InitPhase2()
{
    using namespace tgon;

    auto engine = Application::GetInstance()->GetEngine();

    // ī�޶� �߰�
    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const auto rootWindowSize = Application::GetInstance()->GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(FRect{-halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height)}, -1.0f, 1024.0f);
    this->AddGlobalObject(cameraObject);

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    // �ؽ�ó ������Ʈ �߰�
    auto texture = std::make_shared<tgon::Texture>(Path::GetDesktopDirectory() + "/2.jpg", FilterMode::Bilinear, WrapMode::Repeat, true, false);

    auto object = std::make_shared<GameObject>("introSprite1", new Transform());
    object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
    spriteComponent->SetSprite(std::make_shared<Sprite>(texture));
    this->AddObject(object);
}

void LogoScene::InitPhase3()
{
    using namespace tgon;
    auto engine = Application::GetInstance()->GetEngine();

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();
    
    // ī�޶� �߰�
    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height) }, -1.0f, 1024.0f);
    this->AddGlobalObject(cameraObject);

    //TextureAtlasTree tat(I32Extent2D(4096, 4096), 2);

    //// �ؽ�ó �߰�
    //FontFactory ff;
    //std::shared_ptr<Font> font = ff.GetFont(StringHash(GetDesktopDirectory() + "/maplestory_bold.ttf"));
 
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //float accumulatedXPos = -100.0f;
    //float accumulatedYPos = 0.0f;
    //const wchar_t str[] = L"Hello.My name is Junho";
    //for (int i = 0; i < std::extent<decltype(str)>::value - 1; ++i)
    //{
    //    int32_t fontSize = 30;
    //    auto& glyphData = font->GetGlyphData(str[i], fontSize);

    //    if (i != 0)
    //    {
    //        auto& prevGlyphData = font->GetGlyphData( str[i - 1], fontSize );
    //        accumulatedXPos -= (prevGlyphData.size.width - glyphData.size.width) / 2;

    //        auto kerning = font->GetKerning( str[i - 1], str[i], fontSize );
    //        accumulatedXPos += kerning.x;
    //    }

    //    float xPos = accumulatedXPos + glyphData.bearing.x;
    //    float yPos = accumulatedYPos - glyphData.size.height / 2 + glyphData.bearing.y;

    //    auto object = std::make_shared<GameObject>("introSprite1", new Transform());
    //    object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    //    object->GetTransform()->SetLocalPosition(Vector3( xPos, yPos, 0.0f ));
    //    auto spriteComponent = object->AddComponent<CanvasSpriteRendererComponent>();
    //    auto texture = std::make_shared<Texture>(&glyphData.bitmap[0], glyphData.size, PixelFormat::R8, FilterMode::Point, WrapMode::Clamp, false, false);
    //    spriteComponent->SetSprite(std::make_shared<CanvasSprite>(texture));
    //    this->AddObject(object);

    //    accumulatedXPos += glyphData.advance.x;
    //}
}

class CultureInfo
{

};

namespace tgon
{

}

void LogoScene::InitPhase4()
{
    using namespace tgon;
    
    auto localTimeZone = TimeZoneInfo::Local();
    auto now = DateTime::UtcNow();
    auto c = TimeZoneInfo::ConvertTimeFromUtc(now, localTimeZone);
    auto ch = c.GetHour();
    auto cd = c.GetDay();
    
    auto engine = Application::GetInstance()->GetEngine();

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    // ī�޶� �߰�
    auto cameraObject = std::make_shared<GameObject>( "camera1", new Transform() );
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>( rootWindowSize.width ) * 0.5f;
    const float halfHeight = static_cast<float>( rootWindowSize.height ) * 0.5f;
    cameraObject->AddComponent<CameraComponent>( tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>( rootWindowSize.width ), static_cast<float>( rootWindowSize.height ) }, -1.0f, 1024.0f );
    this->AddGlobalObject( cameraObject );

    FontFactory ff;
    std::shared_ptr<Font> font = ff.CreateFont( StringHash( Path::GetDesktopDirectory() + "/maplestory_bold.ttf" ) );

    auto object = std::make_shared<GameObject>( "introSprite1", new Transform() );
    object->GetTransform()->SetLocalScale( { 1.0f, 1.0f, 1.0f } );
    object->GetTransform()->SetLocalPosition( Vector3( 0.0f, 0.0f, 0.0f ) );
    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
    
    const wchar_t chArray[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvrwxyz가나다라마바사아자차카타파하";
    static TextureAtlas textureAtlas(I32Extent2D(512, 512), PixelFormat::RGBA8888, 6);
    //for (auto ch : chArray)
    {
        const auto& glyphData = font->GetGlyphData('A', 35);
        const auto& glyphData2 = font->GetGlyphData('B', 35);
        textureAtlas.Insert(glyphData.character, ImageView(glyphData.bitmap.get(), glyphData.size, PixelFormat::RGBA8888));
    }

    auto& imageRect = textureAtlas.GetTextureRect(u'가');
    decltype(auto) texture = textureAtlas.GetAtlasTexture();
    decltype(auto) sprite = std::make_shared<Sprite>(texture);
    sprite->SetTextureRect(FRect(imageRect.x, imageRect.y, imageRect.width, imageRect.height));
    spriteComponent->SetSprite(sprite);
    this->AddObject( object );

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
