/**
 * @file    UIRendererModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Graphics/Graphics.h"
#include "Graphics/Camera.h"
#include "Graphics/Material.h"
#include "Graphics/VertexBuffer.h"
#include "UI/UIElement.h"
#include "UI/UIBatch.h"

#include "Module.h"

namespace tgon
{

class UIRendererModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(UIRendererModule)
    
/**@section Constructor */
public:
    explicit UIRendererModule(const std::shared_ptr<Graphics>& graphics) noexcept;

/**@section Method */
public:
    void AddCamera(const std::shared_ptr<Camera>& camera);
    void AddUIElement(const std::shared_ptr<UIElement>& element, int32_t sotringLayer, const Matrix4x4& matWorld);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    void SetMaxSortingLayer(int32_t maxSortingLayer) noexcept;
    int32_t GetMaxSortingLayer() const noexcept;
    std::shared_ptr<Graphics> GetGraphics() noexcept;
    std::shared_ptr<const Graphics> GetGraphics() const noexcept;
    void Update() override;
    void Draw();

private:
    void PrepareDefaultMaterials();
    void UpdateSpriteBatches();
    void FlushSpriteBatches();

/**@section Variable */
private:
    std::shared_ptr<Graphics> m_graphics;
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<std::vector<std::pair<std::shared_ptr<UIElement>, const Matrix4x4&>>> m_sortingLayers;
    std::vector<UIBatch> m_batches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
