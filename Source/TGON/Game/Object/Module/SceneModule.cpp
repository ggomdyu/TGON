#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"
#include "Core/Object/Module/TimeModule.h"
#include "Game/Object/Scene.h"

#include "SceneModule.h"
#include "Graphics/Render/Sprite.h"
#include "Graphics/LowLevel/GraphicsType.h"
#include "Core/Platform/Application.h"
#include "Core/Platform/Window.h"
#include "Core/Math/Mathematics.h"
#include "Core/File/Path.h"

namespace tgon
{
    
    std::shared_ptr<Mesh> m_sharedMesh;
    std::unique_ptr<Sprite> m_txt;
    
SceneModule::SceneModule(std::unique_ptr<Scene> scene, Window& displayTarget, const VideoMode& videoMode) :
    m_renderer(displayTarget, videoMode),
    m_currentScene(std::move(scene))
{
    m_txt.reset(new Sprite(GetDesktopDirectory() + "/1.png"));
    
    auto extent = Application::GetInstance().GetRootWindow().GetSize();
    
    auto matViewProj = Matrix4x4::LookAtRH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    matViewProj *= Matrix4x4::PerspectiveRH(Pi / 8.0f, (float)extent.width / (float)extent.height, 0.1f, 1000.0f);
    auto spriteMatWVP  = Matrix4x4::Translate(0.0f, 0.0f, 0.0f) * matViewProj;
    
    m_txt->SetWorldViewProjectionMatrix(spriteMatWVP);
}
    
SceneModule::SceneModule(Window& displayTarget, const VideoMode& videoMode) :
    SceneModule(nullptr, displayTarget, videoMode)
{
}

SceneModule::~SceneModule() = default;

void SceneModule::Update()
{
    decltype(auto) engine = Engine::GetInstance();

    decltype(auto) timeModule = engine.GetModule<TimeModule>();
    if (timeModule != nullptr)
    {
        m_currentScene->Update(timeModule->GetTickTime());
    }
    
    this->Draw();
}

void SceneModule::Draw()
{
    decltype(auto) graphics = m_renderer.GetGraphics();
    
    graphics.ClearColorDepthBuffer();
    {
        m_txt->Draw(graphics);
//        m_currentScene->Draw();
//        m_spriteBatch.FlushBatch(graphics);
    }
    graphics.SwapBuffer();
}

void SceneModule::ChangeScene(std::unique_ptr<Scene> scene)
{
    m_currentScene = std::move(scene);
}

const Scene& SceneModule::GetCurrentScene() const noexcept
{
    return *m_currentScene;
}

Scene& SceneModule::GetCurrentScene() noexcept
{
    return *m_currentScene;
}

} /* namespace tgon */
