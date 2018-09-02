/**
 * @file    MeshRendererComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Graphics/Render/Material.h"
#include "Graphics/Render/Mesh.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "Component.h"

namespace tgon
{

class TGON_API MeshRendererComponent :
	public Component
{
public:
    TGON_RUNTIME_OBJECT(MeshRendererComponent);

/* @section Public constructor */
public:
    MeshRendererComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
    
/* @section Public destructor */
public:
    virtual ~MeshRendererComponent() override = default;

/* @section Public method */
public:
	virtual void Update() override;
    
    /* @brief   Sets the mesh. */
    void SetMesh(const std::shared_ptr<Mesh>& mesh);
    
    /* @brief   Gets the mesh. */
    const std::shared_ptr<Mesh>& GetMesh() const noexcept;
    
    /* @brief   Sets the material. */
    void SetMaterial(const std::shared_ptr<Material>& material);
    
    /* @brief   Gets the material. */
    const std::shared_ptr<Material>& GetMaterial() const noexcept;
    
/* @section Private variable */
private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
