#include "PrecompiledHeader.h"

#include "Core/Platform/Application.h"

#include "GameSceneModule.h"

namespace tgon
{

void GameSceneModule::Update()
{
    m_currentScene->Update();
}

void GameSceneModule::ChangeScene(GameScene* scene)
{
    m_currentScene.reset(scene);
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
