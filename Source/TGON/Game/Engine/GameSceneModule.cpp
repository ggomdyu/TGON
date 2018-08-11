#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"

#include "GameSceneModule.h"

namespace tgon
{

GameSceneModule::GameSceneModule() :
    GameSceneModule(std::make_unique<GameScene>())
{
}

GameSceneModule::GameSceneModule(std::unique_ptr<GameScene> scene) :
    m_currentScene(std::move(scene))
{
}

void GameSceneModule::Update()
{
    m_currentScene->Update();
}

void GameSceneModule::ChangeScene(std::unique_ptr<GameScene> scene)
{
    m_currentScene = std::move(scene);
}

const GameScene& GameSceneModule::GetCurrentScene() const noexcept
{
    return *m_currentScene;
}

GameScene& GameSceneModule::GetCurrentScene() noexcept
{
    return *m_currentScene;
}

} /* namespace tgon */
