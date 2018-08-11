/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>

#include "Batch.h"
#include "Camera.h"

namespace tgon
{
    
class TGON_API RenderStage final :
    private boost::noncopyable
{
/* @section Public method */
public:
    /* @brief   Adds a mesh into the batch list. */
    void AddBatch(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh);
    
    /* @brief   Adds a batch into the batch list. */
    void AddBatch(const Batch& batch);
    
    void Draw(Graphics& graphics);

/* @section Private variable */
private:
    BatchGroup m_batchGroup;
    
    std::vector<Camera> m_cameraList;
};

} /* namespace tgon */
