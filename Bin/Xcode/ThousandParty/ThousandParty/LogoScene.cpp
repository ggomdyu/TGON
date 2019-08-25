#include "PrecompiledHeader.h"

#include <functional>
#include <atomic>
#include <thread>
#include <fstream>
#include "TGON.h"
#include "IntroScene.h"
#include "LogoScene.h"
#include "Math/Rect.h"
#include "IO/File.h"
#include "Core/Range.h"
#include "Drawing/FontFactory.h"
#include "Graphics/TextureAtlas.h"
#include "String/UnicodeScalar.h"
#include "IO/FileStream.h"
#include "Time/TimeZoneInfo.h"
#include "./../Test/Time/DateTimeTest.h"
#include "./../Test/String/FixedStringTest.h"
#include "./../Test/IO/FileTest.h"
#include "./../Test/IO/FileStreamTest.h"
#include "./../Test/IO/PathTest.h"

std::shared_ptr<tgon::GameObject> object1;
std::shared_ptr<tgon::GameObject> object2;
std::shared_ptr<tgon::GameObject> object3;
std::shared_ptr<tgon::GameObject> object4;
std::shared_ptr<tgon::GameObject> object5;

LogoScene::LogoScene()
{
    using namespace tgon;
    
    m_beginTime = Environment::GetTickCount();

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

    auto engine = Application::GetInstance().GetEngine();

    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height) }, -1.0f, 1024.0f);
    this->AddGlobalObject(cameraObject);

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    auto texture = std::make_shared<Texture>(*Environment::GetFolderPath(Environment::SpecialFolder::Desktop) + "/2.jpg", FilterMode::Bilinear, WrapMode::Repeat, true, false);

    object1 = std::make_shared<GameObject>("introSprite1", new Transform());
    object1->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object1->GetTransform()->SetLocalPosition({ 100.0f, 0.0f, 0.0f });
    m_introSpriteComponent1 = object1->AddComponent<SpriteRendererComponent>(std::make_shared<UISprite>(texture));

    object2 = std::make_shared<GameObject>("introSprite1", new Transform());
    object2->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object2->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    m_introSpriteComponent2 = object2->AddComponent<SpriteRendererComponent>(std::make_shared<UISprite>(texture));

    this->AddObject(object1);
    this->AddObject(object2);
}

void LogoScene::InitPhase2()
{
    using namespace tgon;

    auto engine = Application::GetInstance().GetEngine();

    // ī�޶� �߰�
    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const auto rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
    const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
    const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
    cameraObject->AddComponent<CameraComponent>(FRect{-halfWidth, -halfHeight, static_cast<float>(rootWindowSize.width), static_cast<float>(rootWindowSize.height)}, -1.0f, 1024.0f);
    this->AddGlobalObject(cameraObject);

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();

    // �ؽ�ó ������Ʈ �߰�
    auto texture = std::make_shared<tgon::Texture>(*Environment::GetFolderPath(Environment::SpecialFolder::Desktop) + "/2.jpg", FilterMode::Bilinear, WrapMode::Repeat, true, false);

    auto object = std::make_shared<GameObject>("introSprite1", new Transform());
    object->GetTransform()->SetLocalScale({ 1.0f, 1.0f, 1.0f });
    object->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
    auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
    spriteComponent->SetSprite(std::make_shared<UISprite>(texture));
    this->AddObject(object);
}

void LogoScene::InitPhase3()
{
    using namespace tgon;

    auto engine = Application::GetInstance().GetEngine();

    auto graphicsModule = engine->FindModule<GraphicsModule>();
    graphicsModule->GetGraphics().DisableDepthTest();
    
    // ī�޶� �߰�
    auto cameraObject = std::make_shared<GameObject>("camera1", new Transform());
    const tgon::I32Extent2D rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
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
//template <typename T>
//struct has_begin_end
//{
//    template<typename C>
//    static char(&f(typename std::enable_if_t<
//        std::is_same_v<
//            decltype(static_cast<typename C::const_iterator(C::*)() const>(&C::begin)),
//            typename C::const_iterator(C::*)() const>
//    >*))[1];
//
//    template<typename C>
//    static constexpr char(&f(...))[2];
//
//    static constexpr bool beg_value = sizeof(f<T>(0)) == 1;
//};

template <typename _Type>
struct HasBeginEnd
{
/**@section Enum */
public:
    template <typename _Type2>
    static void TypeCheckFunc(std::enable_if_t<std::is_same_v<
        typename _Type2::iterator(_Type2::*)(),
        decltype(static_cast<typename _Type2::iterator(_Type2::*)()>(&_Type2::begin))
    >>*)
    {
        int n = 3;
    }

    template <typename _Type2>
    static void TypeCheckFunc(...)
    {
        int n = 3;
    }

/**@section Variable */
};

void LogoScene::InitPhase4()
{
    using namespace tgon;

    FixedStringTest().Evaluate();
    DateTimeTest().Evaluate();
    PathTest().Evaluate();
    FileStreamTest().Evaluate();
    
//    Debug::WriteLine(*Environment::GetUserDomainName());
    Debug::WriteLine(*Environment::GetFolderPath(Environment::SpecialFolder::ProgramFiles));
    auto ar = Environment::GetCommandLineArgs();
    auto ac = Environment::GetMachineName();
    int n = 3;
    
//    auto commandLine = Environment::GetCommandLine();
//    auto commandLine2 = Environment::GetCurrentDirectory();
//    auto commandLine3 = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);
//    auto pageSize = Environment::GetSystemPageSize();
//    auto is64P = Environment::Is64BitProcess();
//    auto is64OS = Environment::Is64BitOperatingSystem();
//    auto newLine = Environment::GetNewLine();
//    auto d1 = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);
//    auto d2 = Environment::GetFolderPath(Environment::SpecialFolder::MyMusic);
//    auto d3 = Environment::GetFolderPath(Environment::SpecialFolder::MyVideos);
//    auto d4 = Environment::GetFolderPath(Environment::SpecialFolder::Fonts);
//    auto d5 = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
//    auto d6 = Environment::GetFolderPath(Environment::SpecialFolder::MyPictures);
//    auto d7 = Path::GetInvalidPathChars();
//    auto d8 = Path::GetInvalidFileNameChars();
//    
//    auto a = Path::GetFullPath(u8"ext.png");
//    auto b = Path::GetFullPath(u8"/ext.png");
//    auto c = Path::GetFullPath(u8"\\ext.png");

//    while (true)
//    {
//        auto str = std::to_string(Environment::GetTickCount());
//        Debug::WriteLine(str);
//    }

//    FileStream f("E:/Users/ggomdyu/Desktop/a", FileMode::OpenOrCreate, FileAccess::ReadWrite);
//    for (int i = 0; i < (int)(4096.0 * 1.1); ++i)
//    {
//        if (i > 4095)
//        {
//            f.WriteByte(2);
//        }
//        else
//        {
//            f.WriteByte(1);
//        }
//    }

    //// Range 클래스에서 써보자
    ///*HasBeginEnd<std::vector<int>>::TypeCheckFunc<std::vector<int>>(1);
    //HasBeginEnd<std::vector<int>>::TypeCheckFunc<int>(1);*/
    //
    ///*FileTest().Evaluate();*/
    //
    //char ch[446] {};
    //StringHash s = ch;
    //StringViewHash s2 = "\0\0\0";
   ///* for (auto ch : Range(s2.Begin(), s2.End()))
    //{
    //    int n = 3;
    //}*/
    //FixedString8Hash s3 = ch;
    //
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::Indent();
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::Indent();
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::Unindent();
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::Write(u8"hahaha");
    //Debug::Unindent();
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //Debug::WriteLine(u8"진짜웃겨요!!");
    //
    //auto engine = Application::GetInstance().GetEngine();
    //auto r = DateTime(2001, 10, 12, 0, 0, 0, DateTimeKind::Local);
//  //  auto ct = TimeZoneInfo::ConvertTimeFromUtc(r, TimeZoneInfo::Local());
    //
    //auto k = r.GetKind();
    //if (k == DateTimeKind::Local)
    //{
    //    int n = 3;
    //}
    //
    //bool a342 = File::SetCreationTime(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0,0,0, DateTimeKind::Utc));//9
    //bool a34 = File::SetCreationTimeUtc(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0,0,0, DateTimeKind::Local));
    //bool a35 = File::SetLastAccessTime(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0,0,0, DateTimeKind::Utc));
    //bool a36 = File::SetLastAccessTimeUtc(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0,0,0, DateTimeKind::Local));
    //bool a37 = File::SetLastWriteTime(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0, 0, 0, DateTimeKind::Utc));
    //bool a38 = File::SetLastWriteTimeUtc(u8"E:/Users/ggomdyu/Desktop/1.PNG", DateTime(2001, 10, 12, 0, 0, 0, DateTimeKind::Local));
    //auto graphicsModule = engine->FindModule<GraphicsModule>();
    //graphicsModule->GetGraphics().DisableDepthTest();
    //
    //// ī�޶� �߰�
    //auto cameraObject = std::make_shared<GameObject>( "camera1", new Transform() );
    //const tgon::I32Extent2D rootWindowSize = Application::GetInstance().GetRootWindow()->GetExtent();
    //const float halfWidth = static_cast<float>( rootWindowSize.width ) * 0.5f;
    //const float halfHeight = static_cast<float>( rootWindowSize.height ) * 0.5f;
    //cameraObject->AddComponent<CameraComponent>( tgon::FRect{ -halfWidth, -halfHeight, static_cast<float>( rootWindowSize.width ), static_cast<float>( rootWindowSize.height ) }, -1.0f, 1024.0f );
    //this->AddGlobalObject( cameraObject );
    //
    //FontFactory ff;
    //std::shared_ptr<Font> font = ff.CreateFont( StringHash( Path::GetDesktopDirectory() + "/maplestory_bold.ttf" ) );
    //
    //auto object = std::make_shared<GameObject>( "introSprite1", new Transform() );
    //object->GetTransform()->SetLocalScale( { 1.0f, 1.0f, 1.0f } );
    //object->GetTransform()->SetLocalPosition( Vector3( 0.0f, 0.0f, 0.0f ) );
    //auto spriteComponent = object->AddComponent<SpriteRendererComponent>();
    //
    //const wchar_t chArray[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvrwxyz가나다라마바사아자차카타파하";
    //static TextureAtlas textureAtlas(I32Extent2D(512, 512), PixelFormat::RGBA8888, 6);
    ////for (auto ch : chArray)
    //{
    //    const auto& glyphData = font->GetGlyphData('A', 35);
    //    const auto& glyphData2 = font->GetGlyphData('B', 35);
    //    textureAtlas.Insert(glyphData.character, ImageView(glyphData.bitmap.get(), glyphData.size, PixelFormat::RGBA8888));
    //}
    //
    //auto& imageRect = textureAtlas.GetTextureRect(u'가');
    //decltype(auto) texture = textureAtlas.GetAtlasTexture();
    //decltype(auto) sprite = std::make_shared<UISprite>(texture);
    //sprite->SetTextureRect(FRect(imageRect.x, imageRect.y, imageRect.width, imageRect.height));
    //spriteComponent->SetSprite(sprite);
    //this->AddObject( object );

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
