/**
 * @filename    GameObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include "Core/Object/Object.h"

//#include "../Core/Math/Mathf.h"
//#include "../Component/TransformComponent.h"

#include <vector>

namespace tgon
{

class IComponent;
struct GameContext;

class TGON_API GameObject :
	public Object
{
public:
    TGON_RUNTIME_OBJECT(GameObject)

/* @section Public constructor */
public:
    explicit GameObject(const std::shared_ptr<GameContext>& context);
    GameObject(const GameObject&) = delete;
    virtual ~GameObject() override;

/* @section Public operator */
public:
    GameObject& operator=(const GameObject&) = delete;

/* @section Public method */
public:
    void Update();

/* @section Private variable */
private:
    std::shared_ptr<GameContext> m_context;

    std::vector<std::unique_ptr<IComponent>> m_components;
    std::vector<std::shared_ptr<GameObject>> m_childs;
};

} /* namespace tgon */