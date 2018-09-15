/**
 * @file    RenderStage.h
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

/**@section Public type */
public:
    using CameraHandle = size_t;
    using CameraList = std::vector<std::shared_ptr<Camera>>;

/**@section Public method */
public:
    /**@brief   Adds a mesh into BatchGroup. */
    void AddBatch(const std::shared_ptr<Material>& material, const Batch::DrawPrimitive& drawPrimitive);
    
    /**@brief   Adds a batch into BatchGroup. */
    void AddBatch(const Batch& batch);

    /**@brief   Adds a mesh into SpriteBatchGroup. */
    void AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive);

    /**@brief   Adds a batch into SpriteBatchGroup. */
    void AddSpriteBatch(const SpriteBatch& batch);

    /**@brief   Adds a camera into RenderStage. */
    void AddCamera(const std::shared_ptr<Camera>& camera);

    CameraList& GetCameraList() noexcept;

    const CameraList& GetCameraList() const noexcept;

    /**@brief   Removes the specified camera in RenderStage. */
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
    void Draw(Graphics& graphics);

/**@section Private variable */
private:
    BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    CameraList m_cameraList;
};

} /* namespace tgon */
