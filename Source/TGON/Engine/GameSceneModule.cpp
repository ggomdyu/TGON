#include "PrecompiledHeader.h"

#include "Game/GameScene.h"

#include "GameSceneModule.h"

namespace tgon
{

void GameSceneModule::Update()
{
    m_currentScene->Update();
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
