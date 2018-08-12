/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>

#include "Camera.h"
#include "Batch.h"
#include "SpriteBatch.h"

namespace tgon
{
    
class TGON_API RenderStage final :
    private boost::noncopyable
{
/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch list. */
    void AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive);
    
    /* @brief   Adds a batch into the batch list. */
    void AddBatch(const Batch& batch);

    /* @brief   Adds a mesh into the batch list. */
    void AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);

    /* @brief   Adds a batch into the batch list. */
    void AddSpriteBatch(const SpriteBatch& batch);

    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    std::vector<Camera> m_cameraList;
};

} /* namespace tgon */
