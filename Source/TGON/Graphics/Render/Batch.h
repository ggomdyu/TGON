/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Material.h"
#include "Mesh.h"

#include "../LowLevel/Graphics.h"

namespace tgon
{

class Batch final
{
/* @section Public constructor */
public:
    /* @brief   Initializes the batch with a material. */
    explicit Batch(const std::shared_ptr<Material>& material);

/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch. */
    void AddMesh(const std::shared_ptr<Mesh>& mesh);
    
    /* @brief   Checks whether the specified material can batched. */
    bool CanBatch(const Material& material) const;
    
    /* @brief   Draws all batched meshes. */
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    std::shared_ptr<Material> m_material;
    
    std::vector<std::shared_ptr<Mesh>> m_meshes;
};
    
class BatchGroup final
{
/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch list. */
    void AddBatch(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh);
    
    /* @brief   Adds a batch into the batch list. */
    void AddBatch(const Batch& batch);
    
    /* @brief   Draws all batch list. */
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    std::vector<Batch> m_batches;
};
    
} /* namespace tgon */
