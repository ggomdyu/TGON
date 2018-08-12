/**
 * @file    Component.h
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
     * @brief                   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     */
    SpriteRendererComponent(const std::string& filePath);

    /**
     * @brief                   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     */
    SpriteRendererComponent(std::string&& filePath);

    /**
     * @brief                   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     * @param [in] material     The material to use with this renderer.
     */
    SpriteRendererComponent(const std::string& filePath, const std::shared_ptr<Material>& material) noexcept;

    /**
     * @brief                   Initializes component with specified sprite path.
     * @param [in] filePath     The file path of sprite.
     * @param [in] material     The material to use with this renderer.
     */
    SpriteRendererComponent(std::string&& filePath, const std::shared_ptr<Material>& material) noexcept;

/* @section Public destructor */
public:
    virtual ~SpriteRendererComponent() override = default;

/* @section Public method */
public:
    /* @brief   Updates the component. */
    virtual void Update() override;

/* @section Private variable */
private:
    std::shared_ptr<Material> m_material;

    Sprite m_sprite;

    GraphicsModule* m_graphicsModule;
};

} /* namespace tgon */
