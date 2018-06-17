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
/* @section Private type */
private:
    using BatchedSprites = std::vector<std::shared_ptr<Sprite>>;
    
/* @section Public method */
public:
    void AddSprite(std::shared_ptr<Sprite> sprite);
    void FlushBatch(Graphics& graphics);
    
/* @section Private variable */
private:
    std::vector<BatchedSprites> m_batchedSpritesSet;
};
    
} /* namespace tgon */
