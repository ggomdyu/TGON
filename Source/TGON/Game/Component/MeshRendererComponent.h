/**
 * @file    MeshRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "RendererComponent.h"

namespace tgon
{

class TGON_API MeshRendererComponent :
	public RendererComponent
{
public:
    TGON_DECLARE_RTTI(MeshRendererComponent);

/**@section Constructor */
public:
    MeshRendererComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
    
/**@section Destructor */
public:
    virtual ~MeshRendererComponent() override = default;

/**@section Method */
public:
	virtual void Update() override;
    
    /**@brief   Sets the mesh. */
    void SetMesh(const std::shared_ptr<Mesh>& mesh);
    
    /**@brief   Gets the mesh. */
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;
    
/**@section Variable */
protected:
    std::shared_ptr<Mesh> m_mesh;
};

} /* namespace tgon */
