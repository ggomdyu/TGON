#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"
#include "Core/Object/Module/TimeModule.h"
#include "Game/Object/Scene.h"

#include "SceneModule.h"

namespace tgon
{

SceneModule::SceneModule(std::unique_ptr<Scene> scene, const VideoMode& videoMode, const Window& displayTarget) :
    m_graphics(displayTarget, videoMode),
    m_currentScene(std::move(scene))
{
}
    
SceneModule::SceneModule(const VideoMode& videoMode, const Window& displayTarget) :
    SceneModule(std::make_unique<Scene>(), videoMode, displayTarget)
{
}

SceneModule::~SceneModule() = default;

void SceneModule::Update()
{
    decltype(auto) engine = Application::GetInstance()->GetEngine();

    decltype(auto) timeModule = engine.GetModule<TimeModule>();
    if (timeModule != nullptr)
    {
        m_currentScene->Update(timeModule->GetTickTime());
    }
    
    this->Draw();
}

void SceneModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_currentScene->Draw();
        m_spriteBatch.FlushBatch(m_graphics);
    }
    m_graphics.SwapBuffer();
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
