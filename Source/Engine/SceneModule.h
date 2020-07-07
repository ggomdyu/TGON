#pragma once

#include <string>

#include "Core/Delegate.h"
#include "Game/GameObject.h"

#include "Module.h"

namespace tg
{

enum class NewSceneSetup
{
    EmptyScene,
    DefaultGameObjects,
};

enum class OpenSceneMode
{
    Single,
    Additive,
};

class Scene :
    public RuntimeObject
{
public:
    TGON_RTTI(Scene)

/**@section Method */
public:
    void Initialize();
    void Update();

private:
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};

class SceneManager :
    public Module
{
public:
    TGON_RTTI(SceneManager)

/**@section Type */
public:
    using NewSceneCreatedCallback = Delegate<void(const std::shared_ptr<Scene>&, NewSceneSetup)>;
    using SceneOpeningCallback = Delegate<void(const std::shared_ptr<Scene>&, OpenSceneMode)>;
    using SceneOpenCallback = Delegate<void(const std::shared_ptr<Scene>&, OpenSceneMode)>;

/**@section Method */
public:
    void Update() override;
    void NewScene(NewSceneSetup newSceneSetup);
    void OpenScene(const std::string& path, OpenSceneMode openSceneMode);
    std::shared_ptr<GameObject> Instantiate();

/**@section Event handler */
public:
    SceneOpeningCallback OnOpeningScene;
    SceneOpenCallback OnOpenScene;

/**@section Variable */
public:
    static constexpr auto ModuleStage = ModuleStage::Update;

protected:
    std::shared_ptr<Scene> m_activeScene;
    std::vector<std::shared_ptr<Scene>> m_sceneList;
};

}
