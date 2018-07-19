/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include "Sprite.h"

namespace tgon
{

class SpriteBatch final
{
/* @section Private type */
private:
    using BatchedSprites = std::vector<std::shared_ptr<Sprite>>;
    
/* @section Public method */
public:
    /* @brief   Adds a sprite to sprite batch. */
    void AddSprite(const std::shared_ptr<Sprite>& sprite);
    
    /* @brief   Draws all batched sprites. */
    void FlushBatch(Graphics& graphics);
    
    void Clear();
    
/* @section Private variable */
private:
    std::vector<BatchedSprites> m_batchedSpritesLayer;
};
    
} /* namespace tgon */
