#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"
#include "Core/Object/Module/TimeModule.h"
#include "Game/Object/Scene.h"

#include "SceneManagementModule.h"

namespace tgon
{

SceneManagementModule::SceneManagementModule(std::unique_ptr<Scene> scene, const VideoMode& videoMode, std::shared_ptr<Window> displayTarget) :
    m_graphics(videoMode, displayTarget),
    m_currScene(std::move(scene))
{
}
    
SceneManagementModule::SceneManagementModule(const VideoMode& videoMode, std::shared_ptr<Window> displayTarget) :
    SceneManagementModule(std::make_unique<Scene>(), videoMode, displayTarget)
{
}

SceneManagementModule::~SceneManagementModule() = default;

void SceneManagementModule::Update()
{
    decltype(auto) engine = Application::GetInstance()->GetEngine();

    decltype(auto) timeModule = engine->GetModule<TimeModule>();
    if (timeModule != nullptr)
    {
        m_currScene->Update(timeModule->GetTickTime());
    }
    
    this->Draw();
}

void SceneManagementModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_currScene->Draw();
        m_spriteBatch.FlushBatch(m_graphics);
    }
    m_graphics.SwapBuffer();
}

void SceneManagementModule::ChangeScene(std::unique_ptr<Scene> scene)
{
    m_currScene = std::move(scene);
}

void SceneManagementModule::SetDisplayTarget(std::shared_ptr<Window> displayTarget)
{
    m_displayTarget = displayTarget;
}

std::weak_ptr<const Window> SceneManagementModule::GetDisplayTarget() const noexcept
{
    return m_displayTarget;
}

std::weak_ptr<Window> SceneManagementModule::GetDisplayTarget() noexcept
{
    return m_displayTarget;
}

const Scene* SceneManagementModule::GetCurrentScene() const noexcept
{
    return m_currScene.get();
}

Scene* SceneManagementModule::GetCurrentScene() noexcept
{
    return m_currScene.get();
}


} /* namespace tgon */
