/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <map>
#include <vector>

#include "Engine/IModule.h"
#include "Graphics/Graphics.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Camera.h"

namespace tgon
{
    
class Sprite;
class Material;
class Camera;
    
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
    void AddSprite(const std::shared_ptr<Sprite>& sprite);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveSprite(const std::shared_ptr<Sprite>& sprite);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Variable */
private:
    std::map<int32_t, std::vector<std::shared_ptr<Sprite>>> m_spriteLayer;
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<float> m_spriteVertices;
    VertexBuffer m_spriteVertexBuffer;
    std::vector<SpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
class TGON_API Renderer
{
/**@section Method */
public:
    void Update();
    void Draw(Graphics& graphics);
    void AddCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
/**@section Variable */
public:
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};
    
class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(GraphicsModule);
    
/**@section Constructor */
public:
    GraphicsModule(const Window& window, const VideoMode& videoMode);

/**@section Destructor */
public:
    virtual ~GraphicsModule() override final = default;
    
/**@section Method */
public:
    virtual void Update() override;
    Graphics& GetGraphics() noexcept;
    UIRenderer& GetUIRenderer() noexcept;
    Renderer& GetRenderer() noexcept;
    const Graphics& GetGraphics() const noexcept;
    const UIRenderer& GetUIRenderer() const noexcept;
    const Renderer& GetRenderer() const noexcept;
    
/**@section Method */
private:
    void Draw();

/**@section Variable */
public:
    Graphics m_graphics;
    UIRenderer m_uiRenderer;
    Renderer m_renderer;
};

} /* namespace tgon */
