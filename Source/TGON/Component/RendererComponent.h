/**
 * @file    RendererComponent.h
 * @author  ggomdyu
 * @since   11/02/2018
 */

#pragma once
#include "Engine/GraphicsModule.h"
#include "Graphics/Material.h"

#include "Component.h"

namespace tgon
{

class RendererComponent :
	public Component
{
public:
    TGON_DECLARE_RTTI(RendererComponent)

/**@section Constructor */
public:
    explicit RendererComponent(const std::shared_ptr<Material>& material = nullptr);
    
/**@section Destructor */
public:
    virtual ~RendererComponent() override = 0;

/**@section Method */
public:
    void SetMaterial(const std::shared_ptr<Material>& material);
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;
    
/**@section Variable */
protected:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
