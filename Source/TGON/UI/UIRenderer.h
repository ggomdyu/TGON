/**
 * @file    UIRenderer.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <vector>

#include "Math/Matrix4x4.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

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
    void AddSpritePrimitive(const std::shared_ptr<UISprite>& sprite, const Matrix4x4& matWorld);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    void Update();
    void Draw(Graphics& graphics);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    void DebugRenderTargetDraw(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<UISpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
} /* namespace tgon */
