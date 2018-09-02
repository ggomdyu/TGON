/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Graphics/Render/Mesh.h"
#include "Graphics/Render/Material.h"
#include "Graphics/Render/Sprite.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "Component.h"

namespace tgon
{

class TGON_API SpriteRendererComponent :
	public Component
{
public:
    TGON_RUNTIME_OBJECT(SpriteRendererComponent);

/* @section Public constructor */
public:
    /**
     * @brief   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     */
    explicit SpriteRendererComponent(const std::string& filePath);

    /**
     * @brief   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     */
    explicit SpriteRendererComponent(std::string&& filePath);

/* @section Public destructor */
public:
    virtual ~SpriteRendererComponent() override = default;

/* @section Public method */
public:
    /* @brief   Updates the component. */
    virtual void Update() override;

    /**
     * @brief   Sets the sprite.
     * @param [in] sprite   The reference to the sprite.
     */
    void SetSprite(const Sprite& sprite);

    /* @brief   Gets the sprite. */
    Sprite& GetSprite() noexcept;

    /* @brief   Gets the sprite. */
    const Sprite& GetSprite() const noexcept;

    /**
     * @brief   Sets the color of this sprite.
     * @param [in] color    The reference to the sprite color.
     */
    void SetBlendColor(const Color4f& blendColor);

    /* @brief   Gets the color of this sprite.*/
    Color4f& GetBlendColor() noexcept;

    /* @brief   Gets the color of this sprite. */
    const Color4f& GetBlendColor() const noexcept;

/* @section Private variable */
private:
    Sprite m_sprite;
    std::shared_ptr<TextureMaterial> m_material;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
