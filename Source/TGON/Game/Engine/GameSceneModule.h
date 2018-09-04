/**
 * @file    GameSceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Core/Engine/IModule.h"

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
    virtual void Update() final override;
    
    /* @brief   Changes the current scene. */
    void ChangeScene(GameScene* scene);

    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    const GameScene& GetCurrentScene() const noexcept;
    
    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    GameScene& GetCurrentScene() noexcept;
    
/* @section Private method */
private:
    /* @brief   Draws the managed scene. */
    void Draw();

/* @section Private variable */
private:
    std::unique_ptr<GameScene> m_currentScene;
};

} /* namespace tgon */
