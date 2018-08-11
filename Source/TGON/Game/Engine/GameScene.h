/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>
#include <vector>

#include "../Object/GameObject.h"

namespace tgon
{

class TGON_API GameScene
{
/* @section Public destructor */
public:
    virtual ~GameScene() = default;

/* @section Public method */
public:
    /* @brief   Updates the frame of the scene. */
    virtual void Update();
    
    /* @brief   Adds a GameObject into scene. */
    void AddObject(const std::shared_ptr<GameObject>& object);

    /* @brief   Find a GameObject with the specified object name. */
    GameObject* GetObject(const char* objectName);

    /* @brief   Find a GameObject with the specified object name. */
    const GameObject* GetObject(const char* objectName) const;

/* @section Private variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
};

} /* namespace tgon */
