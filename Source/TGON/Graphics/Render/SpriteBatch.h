/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Core/Math/Rect.h"

#include "../LowLevel/Graphics.h"

#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

namespace tgon
{

class TGON_API SpriteBatch final
{
/**@section Public struct */
public:
    struct DrawPrimitive
    {
        const Matrix4x4& matWorld;
    };

/**@section Public constructor */
public:
    /**@brief   Initializes the batch with a material. */
    explicit SpriteBatch(const std::shared_ptr<TextureMaterial>& material);
    
    /**@brief   Initializes the batch with a material and primitives. */
    explicit SpriteBatch(const std::shared_ptr<TextureMaterial>& material, const std::initializer_list<DrawPrimitive>& drawPrimitives);

/**@section Public method */
public:
    /**@brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const std::shared_ptr<Mesh>& mesh, const Matrix4x4& matWVP);
    
    /**@brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const DrawPrimitive& drawPrimitive);

    /**@brief   Checks whether the specified material can batched. */
    bool CanBatch(const std::shared_ptr<TextureMaterial>& material) const;
    
    /**@brief   Draws all of the batched primitives. */
    void Draw(Graphics& graphics, const Camera& camera);

    /**@brief   Gets all of the batched primitives. */
    std::vector<DrawPrimitive>& GetDrawPrimitives() noexcept;

    const std::vector<DrawPrimitive>& GetDrawPrimitives() const noexcept;

/**@section Private variable */
private:
    std::shared_ptr<TextureMaterial> m_material;
    
    std::vector<DrawPrimitive> m_drawPrimitives;
};
    
class TGON_API SpriteBatchGroup final
{
/**@section Public constructor */
public:
    SpriteBatchGroup();

/**@section Public method */
public:
    /**@brief   Adds a mesh into the batch list. */
    void AddSpriteBatch(const std::shared_ptr<TextureMaterial>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);
    
    /**@brief   Adds a batch into the batch list. */
    void AddSpriteBatch(const SpriteBatch& batch);
    
    /**@brief   Flushes all the batch in list. */
    void FlushSpriteBatch(Graphics& graphics, const Camera& camera);

/**@section Private variable */
private:
    std::shared_ptr<Mesh> m_quad;

    std::vector<SpriteBatch> m_spriteBatches;
};
    
} /* namespace tgon */
