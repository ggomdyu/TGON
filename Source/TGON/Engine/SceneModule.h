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
    TGON_DECLARE_RTTI(SceneModule);

/**@section Destructor */
public:
    virtual ~SceneModule() override final = default;

/**@section Method */
public:
    /**@brief   Updates the frame of scene. */
    virtual void Update() override;

    void ChangeScene(Scene* scene);
    Scene& GetCurrentScene() noexcept;
    const Scene& GetCurrentScene() const noexcept;
    
/**@section Variable */
private:
    std::unique_ptr<Scene> m_currScene;
};

}
