/**
 * @file    GameSceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Core/Engine/IModule.h"
#include "Core/debug/Log.h"

#include "GameScene.h"

namespace tgon
{

class TGON_API GameSceneModule final :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(GameSceneModule);

/* @section Public destructor */
public:
    virtual ~GameSceneModule() final override = default;

/* @section Public method */
public:
    /* @brief   Updates the frame of scene. */
    virtual void Update() override
    {
        m_currentScene->Update();
    }

    /* @brief   Changes the current scene. */
    template <typename _SceneType, typename... _ArgTypes>
    void ChangeScene(_ArgTypes&&... args)
    {
        m_currentScene = std::make_unique<_SceneType>(std::forward<_ArgTypes>(args)...);
    }

    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    const GameScene& GetCurrentScene() const noexcept
    {
        return *m_currentScene;
    }

    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    GameScene& GetCurrentScene() noexcept
    {
        return *m_currentScene;
    }
    
/* @section Private method */
private:

/* @section Private variable */
private:
    std::unique_ptr<GameScene> m_currentScene;
};

} /* namespace tgon */
