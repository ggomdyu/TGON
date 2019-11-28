/**
 * @file    SceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>

#include "Game/Scene.h"

#include "Module.h"

namespace tgon
{

class SceneModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(SceneModule)

/**@section Destructor */
public:
    ~SceneModule() override final = default;

/**@section Method */
public:
    void Update() override;

    template <typename _SceneType, typename... _Args>
    void ChangeScene(_Args&&... args);
    
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
