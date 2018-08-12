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
    explicit SpriteRendererComponent(const std::string& filePath);

    /**
     * @brief                   Initializes component with specified sprite path.
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

/* @section Private variable */
private:
    Sprite m_sprite;

    std::shared_ptr<Material> m_material;

    GraphicsModule* m_graphicsModule;
};

} /* namespace tgon */
