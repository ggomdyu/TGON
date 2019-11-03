/**
 * @file    UIRenderer.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Graphics/VertexBuffer.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "Text/StringHash.h"

#include "UISpriteBatch.h"

namespace tgon
{

class TGON_API UIRenderer
{
/**@section Constructor */
public:
    UIRenderer();
    
/**@section Method */
public:
    void AddCamera(const std::shared_ptr<Camera>& camera);
    void AddPrimitive(const std::shared_ptr<UISprite>& sprite, int32_t sotringLayer, const Matrix4x4& matWorld);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    void SetMaxSortingLayer(int32_t maxSortingLayer) noexcept;
    int32_t GetMinSortingLayer() const noexcept;
    int32_t GetMaxSortingLayer() const noexcept;
    void Update();
    void Draw(Graphics& graphics);
    
private:
    void PrepareDefaultMaterials();
    void UpdateSpriteBatches();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<std::vector<std::pair<std::shared_ptr<UISprite>, const Matrix4x4&>>> m_sortingLayers;
    std::vector<UISpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
} /* namespace tgon */
