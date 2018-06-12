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
    SpriteComponent() = default;
    SpriteComponent(const std::string& filePath);
    SpriteComponent(const Sprite& imagePath);
    SpriteComponent(Sprite&& imagePath);

/* @section Public destructor */
public:
    virtual ~SpriteComponent() override = default;

/* @section Public method */
public:
    virtual void Update() override {}
    
    void SetSprite(const std::string& filePath);
    void SetSprite(const Sprite& imagePath);
    void SetSprite(Sprite&& imagePath);
    const Sprite& GetSprite() const noexcept;
    Sprite& GetSprite() noexcept;
    
/* @section Private variable */
private:
    Sprite m_sprite;
};

} /* namespace tgon */
