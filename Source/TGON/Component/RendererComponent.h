/**
 * @file    RendererComponent.h
 * @author  ggomdyu
 * @since   11/02/2018
 */

#pragma once
#include "Component.h"

namespace tgon
{

class Material;
class GraphicsModule;

class TGON_API RendererComponent :
	public Component
{
public:
    TGON_DECLARE_RTTI(RendererComponent);

/**@section Constructor */
public:
    RendererComponent();
    explicit RendererComponent(const std::shared_ptr<Material>& material);
    
/**@section Destructor */
public:
    virtual ~RendererComponent() override = 0;

/**@section Method */
public:
    /**@brief   Sets the material. */
    void SetMaterial(const std::shared_ptr<Material>& material);
    
    /**@brief   Gets the material. */
    std::shared_ptr<Material> GetMaterial() noexcept;

    /**@brief   Gets the material. */
    std::shared_ptr<const Material> GetMaterial() const noexcept;
    
/**@section Variable */
protected:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
