/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>

#include "Core/Object/CoreObject.h"

#include "Batch.h"
#include "SpriteBatch.h"

namespace tgon
{
    
class TGON_API RenderStage final :
    public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(RenderStage);

/* @section Public type */
public:
    using CameraHandle = size_t;

/* @section Public method */
public:
    /* @brief   Adds a mesh into the BatchGroup. */
    void AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive);
    
    /* @brief   Adds a batch into the BatchGroup. */
    void AddBatch(const Batch& batch);

    /* @brief   Adds a mesh into the SpriteBatchGroup. */
    void AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);

    /* @brief   Adds a batch into the SpriteBatchGroup. */
    void AddSpriteBatch(const SpriteBatch& batch);

    /* @brief   Adds a camera into the RenderStage. */
    void AddCamera(const std::shared_ptr<Camera>& camera);

    /* @brief   Removes the specified camera in the RenderStage. */
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
