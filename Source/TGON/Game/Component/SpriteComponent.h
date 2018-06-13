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
    SpriteComponent(const std::shared_ptr<Sprite>& sprite);

/* @section Public destructor */
public:
    virtual ~SpriteComponent() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void Draw(Graphics& graphics);
    void Draw(SpriteBatch& spriteBatch);
    const std::shared_ptr<Sprite>& GetSprite() const noexcept;
    std::shared_ptr<Sprite>& GetSprite() noexcept;
    
/* @section Private variable */
private:
    std::shared_ptr<Sprite> m_sprite;
};

} /* namespace tgon */
