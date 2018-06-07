/**
 * @filename    SpriteBatch.h
 * @author      ggomdyu
 * @since       06/03/2018
 */

#pragma once
#include "Sprite.h"

namespace tgon
{

class SpriteBatch
{
private:
    using BatchedSprites = std::vector<std::shared_ptr<Sprite>>;
    
public:
    void AddSprite(const std::shared_ptr<Sprite>& sprite);
    void FlushBatch(GraphicsContext& context);
    
/* @section Private variable */
private:
    std::vector<BatchedSprites> m_batchedSpritesSet;
};
    
} /* namespace tgon */
