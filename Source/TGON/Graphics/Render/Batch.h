/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "MeshRenderer.h"

namespace tgon
{
    
class Material;
class MeshRenderer;
class Graphics;
    
class Batch final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the batch with a material. */
    explicit Batch(const std::shared_ptr<Material>& material);

    /* @brief   Initializes the batch with a material and mesh renderer. */
    explicit Batch(const MeshRenderer& meshRenderer);
    
/* @section Public method */
public:
    /* @brief   Adds a mesh renderer into the batch. */
    void AddMeshRenderer(const MeshRenderer& meshRenderer);
    
    /* @brief   Checks whether the specified material can batched. */
    bool CanBatch(const Material& material) const;
    
    /* @brief   Draws all batched meshes. */
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    std::shared_ptr<Material> m_material;
    
    std::vector<MeshRenderer> m_meshRenderers;
};
    
class BatchGroup final
{
/* @section Public method */
public:
    /**
     * @brief   Adds a mesh renderer into the batch.
     * @details
     */
    void AddMeshRenderer(const MeshRenderer& meshRenderer);
    
    /* @brief   Adds a batch into the batch list. */
    void AddBatch(const Batch& batch);
    
    /* @brief   Draws all batch list. */
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    std::vector<Batch> m_batches;
};
    
} /* namespace tgon */
