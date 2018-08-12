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
    using CameraHandle = int32_t;

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
    CameraHandle AddCamera(const Camera& camera);

    /* @brief   Gets the camera with specified camera handle. */
    Camera& GetCamera(CameraHandle cameraHandle);

    /* @brief   Gets the camera with specified camera handle. */
    const Camera& GetCamera(CameraHandle cameraHandle) const;

    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    std::vector<Camera> m_cameraList;
};

} /* namespace tgon */
