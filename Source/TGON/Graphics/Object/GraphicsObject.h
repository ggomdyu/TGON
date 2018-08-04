/**
 * @file    GraphicsObject.h
 * @author  ggomdyu
 * @since   08/02/2018
 */

#pragma once
#include "Core/Object/CoreObject.h"
#include "Transform.h"

namespace tgon
{

class TGON_API GraphicsObject :
    public CoreObject
{
/* @brief   Public destructor */
public:
    virtual ~GraphicsObject() override = default;

/* @brief   Public method */
public:
    virtual void Update() override;
    
    /* @brief   Gets the transform. */
    Transform& GetTransform() noexcept;
    
    /* @brief   Gets the transform. */
    const Transform& GetTransform() const noexcept;
    
/* @brief   Private variable */
private:
    Transform m_transform;
};
    
} /* namespace tgon */
