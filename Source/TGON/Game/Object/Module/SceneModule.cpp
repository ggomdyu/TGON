#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"
#include "Core/Object/Module/TimeModule.h"
#include "Game/Object/Scene.h"

#include "SceneModule.h"

namespace tgon
{

SceneModule::SceneModule(std::unique_ptr<Scene> scene, Window& displayTarget, const VideoMode& videoMode) :
    m_renderer(displayTarget, videoMode),
    m_currentScene(std::move(scene))
{
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
        m_currentScene->Draw();
        m_spriteBatch.FlushBatch(graphics);
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
