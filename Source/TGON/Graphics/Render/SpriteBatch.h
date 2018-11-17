/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Core/Math/Rect.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Color.h"

namespace tgon
{

class Material;
class Mesh;
class Graphics;
class Camera;
class Sprite;

class TGON_API SpriteBatch final
{
/**@section Public constructor */
public:
    SpriteBatch();

    SpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld);
    
/**@section Private constructor */
private:
    SpriteBatch(const Color4f* blendColor, const std::shared_ptr<Sprite>* sprite, const std::shared_ptr<Material>* material, const Matrix4x4* matWorld);
    
/**@section Public method */
public:
    void AddWorldMatrix(const Matrix4x4& matWorld);
    
    /**@brief   Draws all of the draw primitive. */
    void Draw(Graphics& graphics, const Camera& camera);
    
    /**@brief   Checks whether the specified SpriteBatch can be batched with this class. */
    bool CanBatch(const SpriteBatch& spriteBatch) const;
    
    /**@brief   Checks whether the specified parameters can be batched with this class. */
    bool CanBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material) const;
    
    const Color4f& GetBlendColor() const noexcept;

    std::shared_ptr<Sprite>& GetSprite() noexcept;

    std::shared_ptr<const Sprite> GetSprite() const noexcept;

    std::shared_ptr<Material>& GetMaterial() noexcept;

    std::shared_ptr<const Material> GetMaterial() const noexcept;

/**@section Private variable */
private:
    std::vector<const Matrix4x4*> m_matWorlds;
    
    const Color4f* m_blendColor;

    const std::shared_ptr<Sprite>* m_sprite;

    const std::shared_ptr<Material>* m_material;
};
    
class TGON_API SpriteBatchGroup final
{
/**@section Public constructor */
public:
    SpriteBatchGroup();

/**@section Public method */
public:
    /**@brief   Adds a SpriteBatch into the group. */
    void AddSpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld);

    /**@brief   Gets all of the sprite batches. */
    const std::vector<SpriteBatch>& GetSpriteBatches() const noexcept;

    /**@brief   Flushes all of the sprites in batch list. */
    void FlushBatch(Graphics& graphics, const Camera& camera);

/**@section Private variable */
private:
    std::shared_ptr<Mesh> m_quad;

    std::vector<SpriteBatch> m_spriteBatches;
};
    
} /* namespace tgon */
