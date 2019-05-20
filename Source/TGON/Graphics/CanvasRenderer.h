/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <map>
#include <vector>

#include "Math/Matrix4x4.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/CanvasSpriteBatch.h"

namespace tgon
{
    
class CanvasSprite;
class Material;
class Camera;
class Graphics;
    
class TGON_API CanvasRenderer
{
/**@section Constructor */
public:
    CanvasRenderer();
    
/**@section Method */
public:
    void Update();
    void Draw(Graphics& graphics);
    void AddCamera(const std::shared_ptr<Camera>& camera);
    void AddSpritePrimitive(const std::shared_ptr<CanvasSprite>& sprite, const Matrix4x4& matWorld);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<CanvasSpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
} /* namespace tgon */