/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <map>
#include <vector>

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
    void AddSprite(const std::shared_ptr<CanvasSprite>& sprite);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveSprite(const std::shared_ptr<CanvasSprite>& sprite);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Variable */
private:
    std::vector<std::shared_ptr<CanvasSprite>> m_sprites;
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<CanvasSpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
} /* namespace tgon */
