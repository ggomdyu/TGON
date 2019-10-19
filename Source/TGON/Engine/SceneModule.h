/**
 * @file    SceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Engine/IModule.h"

namespace tgon
{

class Scene;

class TGON_API SceneModule final :
    public IModule
{
public:
    TGON_DECLARE_RTTI(SceneModule)

/**@section Destructor */
public:
    virtual ~SceneModule() override final = default;

/**@section Method */
public:
    /**@brief   Updates the frame of scene. */
    virtual void Update() override;

    template <typename _SceneType, typename... _Args>
    void ChangeScene(_Args&&... args);
    Scene& GetCurrentScene() noexcept;
    const Scene& GetCurrentScene() const noexcept;
    
/**@section Variable */
private:
    std::unique_ptr<Scene> m_currScene;
};

template <typename _SceneType, typename ..._Args>
inline void SceneModule::ChangeScene(_Args&&... args)
{
    m_currScene = std::make_unique<_SceneType>(std::forward<_Args>(args)...);
    m_currScene->Initialize();
}

} /* namespace tgon */
