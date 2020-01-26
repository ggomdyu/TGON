/**
 * @file    SceneModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <unordered_map>

#include "Game/GameObject.h"

#include "Module.h"

namespace tgon
{

using Scene = GameObject;

class SceneModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(SceneModule)

/**@section Method */
public:
    void Update() override;
    void ChangeScene(const std::shared_ptr<Scene>& scene);

/**@section Variable */
protected:
    std::shared_ptr<Scene> m_currScene;
    std::shared_ptr<Scene> m_nextScene;
};

} /* namespace tgon */
