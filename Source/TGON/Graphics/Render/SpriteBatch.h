/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Core/Math/Rect.h"
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
    struct DrawPrimitive
    {
        bool isEnableScissorRect;
        FRect scissorRect;
        Color4f blendColor;
        std::shared_ptr<Sprite> sprite;
        std::shared_ptr<Material> material;
    };

/**@section Public constructor */
public:
    /**@brief   Initializes the batch. */
    SpriteBatch() = default;

    /**@brief   Initializes the batch with a sprite. */
    explicit SpriteBatch(const DrawPrimitive& drawPrimitive);
    
/**@section Public method */
public:
    /**@brief   Adds a draw primitive into the batch. */
    void AddDrawPrimitive(const DrawPrimitive& drawPrimitive);
    
    /**@brief   Checks whether the specified draw primitive can be batched. */
    bool CanBatch(const DrawPrimitive& drawPrimitive) const;
    
    /**@brief   Draws all of the batched sprites. */
    void Draw(Graphics& graphics, const Camera& camera);
    
    std::vector<DrawPrimitive>& GetDrawPrimitives() noexcept;

    const std::vector<DrawPrimitive>& GetDrawPrimitives() const noexcept;

    /**@brief   Gets all of the batched sprites. */

/**@section Private variable */
private:
    std::vector<DrawPrimitive> m_drawPrimitives;
};
    
class TGON_API SpriteBatchGroup final
{
/**@section Public constructor */
public:
    SpriteBatchGroup(){};

/**@section Public method */
public:
    /**@brief   Adds a sprite into the batch. */
    void AddSprite(const Sprite& sprite){};
    
    /**@brief   Flushes all of the sprites in batch list. */
    void FlushBatch(Graphics& graphics, const Camera& camera){};

/**@section Private variable */
private:
    std::shared_ptr<Mesh> m_quad;

    std::vector<SpriteBatch> m_spriteBatches;
};
    
} /* namespace tgon */
