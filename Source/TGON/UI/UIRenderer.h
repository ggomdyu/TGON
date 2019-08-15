/**
 * @file    UIRenderer.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <map>
#include <vector>

#include "Math/Matrix4x4.h"
#include "Graphics/VertexBuffer.h"

#include "UISpriteBatch.h"

// Todo: remove below headers
#include "Platform/Application.h"
#include "Graphics/RenderTarget.h"

namespace tgon
{
    
class UISprite;
class Material;
class Camera;
class Graphics;
    
class TGON_API UIRenderer
{
/**@section Constructor */
public:
    UIRenderer();
    
/**@section Method */
public:
    void Update();
    void Draw(Graphics& graphics);
    void AddCamera(const std::shared_ptr<Camera>& camera);
    void AddSpritePrimitive(const std::shared_ptr<UISprite>& sprite, const Matrix4x4& matWorld);
//    void AddSpriteBatch(const CanvasSpriteBatch& )
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    void DebugRenderTargetDraw(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    VertexBuffer m_quadVertexBuffer;
    std::vector<UISpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
    
    // For test
    RenderTarget m_renderTarget;
    std::shared_ptr<Material> m_inverseMaterial;
};
    
}
