/**
 * @filename    SpriteComponent.h
 * @author      ggomdyu
 * @since       06/08/2018
 */

#pragma once
#include "Graphics/Render/Sprite.h"

#include "Component.h"

namespace tgon
{

class TGON_API SpriteComponent :
	public Component
{
public:
    TGON_RUNTIME_OBJECT(SpriteComponent);

/* @section Public constructor */
public:
    using Component::Component;

/* @section Public destructor */
public:
    virtual ~SpriteComponent() override = default;

/* @section Public method */
public:
	virtual void Update() override;
    
/* @section Private variable */
private:
    Sprite m_sprite;
};

} /* namespace tgon */
