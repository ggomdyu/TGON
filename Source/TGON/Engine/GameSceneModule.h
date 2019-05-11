/**
 * @file    GameSceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Engine/IModule.h"

namespace tgon
{

class GameScene;

class TGON_API GameSceneModule final :
    public IModule
{
public:
    TGON_DECLARE_RTTI(GameSceneModule);

/**@section Destructor */
public:
    virtual ~GameSceneModule() override final = default;

/**@section Method */
public:
    /**@brief   Updates the frame of scene. */
    virtual void Update() override;

    /**@brief   Changes the current scene. */
    template <typename _SceneType, typename... _ArgTypes>
    void ChangeScene(_ArgTypes&&... args);

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
    
/**@section Variable */
private:
    std::unique_ptr<GameScene> m_currentScene;
};

template<typename _SceneType, typename ..._ArgTypes>
inline void GameSceneModule::ChangeScene(_ArgTypes && ...args)
{
    m_currentScene = std::make_unique<_SceneType>(std::forward<_ArgTypes>(args)...);
}

} /* namespace tgon */
