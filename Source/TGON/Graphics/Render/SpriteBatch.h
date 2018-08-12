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

class TGON_API SpriteBatch final
{
/* @section Public struct */
public:
    struct DrawPrimitive
    {
        const Matrix4x4* matWVP;
    };

/* @section Public constructor */
public:
    /* @brief   Initializes the batch with a material. */
    explicit SpriteBatch(const std::shared_ptr<Material>& material);
    
    /* @brief   Initializes the batch with a material and primitives. */
    explicit SpriteBatch(const std::shared_ptr<Material>& material, const std::initializer_list<DrawPrimitive>& drawPrimitives);

/* @section Public method */
public:
    /* @brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const std::shared_ptr<Mesh>& mesh, const Matrix4x4* matWVP);
    
    /* @brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const DrawPrimitive& drawPrimitive);

    /* @brief   Checks whether the specified material can batched. */
    bool CanBatch(const std::shared_ptr<Material>& material) const;
    
    /* @brief   Draws all batched primitives. */
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    std::shared_ptr<Material> m_material;
    
    std::vector<DrawPrimitive> m_drawPrimitives;
};
    
class TGON_API SpriteBatchGroup final
{
/* @section Public constructor */
public:
    SpriteBatchGroup();

/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch list. */
    void AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);
    
    /* @brief   Adds a batch into the batch list. */
    void AddSpriteBatch(const SpriteBatch& batch);
    
    /* @brief   Flushes all the batch in list. */
    void FlushSpriteBatch(Graphics& graphics);

/* @section Private variable */
private:
    std::shared_ptr<Mesh> m_quadMesh;

    std::vector<SpriteBatch> m_spriteBatches;
};
    
} /* namespace tgon */
