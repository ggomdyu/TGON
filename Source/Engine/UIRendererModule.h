/**
 * @file    UIRendererModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <vector>

#include "Graphics/VertexBuffer.h"
#include "Math/Matrix4x4.h"

#include "Module.h"

namespace tgon
{

class Camera;
class Material;
class Graphics;
class Window;
class UIBatch;
class UIElement;

class UIRendererModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(UIRendererModule)
    
/**@section Type */
public:
    using SortingLayer = int32_t;

/**@section Constructor */
public:
    explicit UIRendererModule(const std::shared_ptr<Graphics>& graphics) noexcept;

/**@section Method */
public:
    void AddPrimitive(const std::shared_ptr<UIElement>& element, SortingLayer sotringLayer, const Matrix4x4& matWorld);
    void AddSubCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveSubCamera(const std::shared_ptr<Camera>& camera);
    void SetMaxSortingLayer(SortingLayer sortingLayer);
    void Update() override;
    void Draw();

private:
    static std::shared_ptr<Camera> CreateMainCamera(const std::shared_ptr<Window>& displayWindow);
    void UpdateCameras();
    void UpdateSpriteBatches();
    void FlushSpriteBatches();

/**@section Variable */
private:
    std::shared_ptr<Graphics> m_graphics;
    std::shared_ptr<Material> m_uiMaterial;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<float> m_spriteVertices;
    std::vector<UIBatch> m_spriteBatches;
    std::vector<std::vector<std::pair<std::shared_ptr<UIElement>, const Matrix4x4&>>> m_sortingLayers;
    std::shared_ptr<Camera> m_mainCamera;
    std::vector<std::shared_ptr<Camera>> m_subCameras;
};

} /* namespace tgon */
