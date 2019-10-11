/**
 * @file    UIRenderer.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <set>

#include "Graphics/VertexBuffer.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"
#include "String/StringHash.h"

#include "UISpriteBatch.h"

namespace tgon
{

class UISortingLayer
{
/**@section Constructor */
public:
    explicit UISortingLayer(const StringHash& sortingLayerName);
    explicit UISortingLayer(StringHash&& sortingLayerName);

/**@section Method */
public:
    void AddPrimitive(const std::shared_ptr<UISprite>& sprite, const Matrix4x4& matWorld);
    
/**@section Variable */
private:
    StringHash m_sortingLayerName;
    std::vector<UISpriteBatch> m_spriteBatches;
};

class TGON_API UIRenderer
{
/**@section Constructor */
public:
    UIRenderer();
    
/**@section Method */
public:
    void AddCamera(const std::shared_ptr<Camera>& camera);
    void AddPrimitive(const std::shared_ptr<UISprite>& sprite, const Matrix4x4& matWorld);
    void AddSortingLayer(const StringHash& sortingLayerName);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveSortingLayer(const StringViewHash& sortingLayerName);
    void Update();
    void Draw(Graphics& graphics);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<UISortingLayer> m_sortingLayers;
    std::set<StringHash> m_sortingLayer;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
} /* namespace tgon */
