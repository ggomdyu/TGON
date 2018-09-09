/**
 * @file    SpriteRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Core/Platform/Application.h"
#include "Graphics/Render/Mesh.h"
#include "Graphics/Render/Material.h"
#include "Graphics/Render/Sprite.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "../Object/GameObject.h"

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
    explicit SpriteRendererComponent(const std::string& filePath) :
        m_sprite(filePath),
        m_material(std::make_shared<TextureMaterial>(m_sprite.GetTexture())),
        m_graphicsModule(Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>())
    {
    }

    /**
     * @brief   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     */
    explicit SpriteRendererComponent(std::string&& filePath) :
        m_sprite(std::move(filePath)),
        m_material(std::make_shared<TextureMaterial>(m_sprite.GetTexture())),
        m_graphicsModule(Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>())
    {
    }

/* @section Public destructor */
public:
    virtual ~SpriteRendererComponent() override = default;

/* @section Public method */
public:
    /* @brief   Updates the component. */
    virtual void Update() override
    {
        m_graphicsModule->GetRenderStage().AddSpriteBatch(m_material, { GetOwner()->GetTransform().GetWorldMatrix() });
    }

    /**
     * @brief   Sets the sprite.
     * @param [in] sprite   The reference to the sprite.
     */
    void SetSprite(const Sprite& sprite)
    {
        m_sprite = sprite;
    }

    /* @brief   Gets the sprite. */
    Sprite& GetSprite() noexcept
    {
        return m_sprite;
    }

    /* @brief   Gets the sprite. */
    const Sprite& GetSprite() const noexcept
    {
        return m_sprite;
    }

    /**
     * @brief   Sets the color of this sprite.
     * @param [in] color    The reference to the sprite color.
     */
    void SetBlendColor(const Color4f& blendColor)
    {
        m_material->SetBlendColor(blendColor);
    }

    /* @brief   Gets the color of this sprite.*/
    Color4f& GetBlendColor() noexcept
    {
        return m_material->GetBlendColor();
    }

    /* @brief   Gets the color of this sprite. */
    const Color4f& GetBlendColor() const noexcept
    {
        return m_material->GetBlendColor();
    }

/* @section Private variable */
private:
    Sprite m_sprite;
    std::shared_ptr<TextureMaterial> m_material;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
