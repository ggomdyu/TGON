#include "PrecompiledHeader.h"

#include "Graphics/ShaderProgram.h"
#include "Graphics/FVF.h"
#include "Graphics/MeshUtility.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Sprite.h"
#include "Graphics/Material.h"
#include "Platform/Window.h"

#include "GraphicsModule.h"

namespace tgon
{
    
UIRenderer::UIRenderer() :
    m_spriteVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_T2F), offsetof(V3F_T2F, uv))
    })
{
    this->PrepareDefaultMaterials();
}

void UIRenderer::Update()
{
    m_spriteBatches.clear();
    m_spriteVertices.clear();
    
    for (const auto& sprites : m_spriteLayer)
    {
        for (const auto& sprite : sprites.second)
        {
            if (m_spriteBatches.empty())
            {
                m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), 0));
            }
            else if (m_spriteBatches.back().CanBatch(*sprite) == false)
            {
                m_spriteBatches.push_back(SpriteBatch(sprite->GetTexture(), sprite->GetBlendMode(), sprite->IsEnableScissorRect(), sprite->GetScissorRect(), sprite->GetTextureRect(), static_cast<int32_t>(m_spriteVertices.size())));
            }
            
            m_spriteBatches.back().Merge(*sprite, &m_spriteVertices);
        }
    }
    
    m_spriteVertexBuffer.SetData(m_spriteVertices.data(), m_spriteVertices.size() * sizeof(m_spriteVertices[0]), false);
    m_spriteVertexBuffer.Use();
}

void UIRenderer::Draw(Graphics& graphics)
{
    //#ifndef NDEBUG
    //    if (m_cameraList.size() <= 0)
    //    {
    //        Log(LogLevel::Debug, "You have no camera but trying to draw.\n");
    //    }
    //#endif
    
    //    static auto quad = MeshUtility::GetSharedQuad();
    //    quad->Use();
    
    this->FlushSpriteBatches(graphics);
}

void UIRenderer::AddSprite(const std::shared_ptr<Sprite>& sprite)
{
    m_spriteLayer[sprite->GetLayer()].push_back(sprite);
}
    
bool UIRenderer::RemoveSprite(const std::shared_ptr<Sprite>& sprite)
{
    auto& sprites = m_spriteLayer[sprite->GetLayer()];
    auto iter = std::find_if(sprites.begin(), sprites.end(), [&](const std::shared_ptr<Sprite>& item)
    {
        return item == sprite;
    });
    if (iter == sprites.end())
    {
        return false;
    }
    
    sprites.erase(iter);
    return true;
}

void UIRenderer::PrepareDefaultMaterials()
{
    m_uiMaterial = std::make_shared<Material>(g_positionUVVert, g_positionUVFrag);
}

void UIRenderer::FlushSpriteBatches(Graphics& graphics)
{
    m_uiMaterial->Use();
    
    for (auto& camera : m_cameraList)
    {
        m_uiMaterial->GetShaderProgram().SetParameterMatrix4fv("g_uWVP", camera->GetViewProjectionMatrix()[0]);
        
        for (auto& spriteBatch : m_spriteBatches)
        {
            spriteBatch.FlushBatch(graphics);
        }
    }
}

void UIRenderer::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool UIRenderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& item)
    {
        return item == camera;
    });
    if (iter == m_cameraList.end())
    {
        return false;
    }
    
    m_cameraList.erase(iter);
    return true;
}

void Renderer::Update()
{
}
    
void Renderer::Draw(Graphics& graphics)
{
}
    
void Renderer::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool Renderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& comp)
                             {
                                 return comp == camera;
                             });
    
    if (iter != m_cameraList.end())
    {
        m_cameraList.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}
    
GraphicsModule::GraphicsModule(const Window& window, const VideoMode& videoMode) :
    m_graphics(window, videoMode)
{
    auto windowSize = window.GetSize();
    m_graphics.SetViewport(0, 0, windowSize.width, windowSize.height);
    m_graphics.SetClearColor(videoMode.clearColor);
    m_graphics.SetCullMode(CullMode::CW);
    m_graphics.EnableDepthTest();
    m_graphics.EnableBlend();
    m_graphics.SetBlendMode(BlendMode::Alpha);
}
    
void GraphicsModule::Update()
{
    m_renderer.Update();
    m_uiRenderer.Update();
    
    this->Draw();
}

void GraphicsModule::Draw()
{
    m_graphics.ClearColorDepthBuffer();
    {
        m_renderer.Draw(m_graphics);
        m_uiRenderer.Draw(m_graphics);
    }
    m_graphics.SwapBuffer();
}
    
Graphics& GraphicsModule::GetGraphics() noexcept
{
    return m_graphics;
}

const Graphics& GraphicsModule::GetGraphics() const noexcept
{
    return m_graphics;
}
    
UIRenderer& GraphicsModule::GetUIRenderer() noexcept
{
    return m_uiRenderer;
}

const UIRenderer& GraphicsModule::GetUIRenderer() const noexcept
{
    return m_uiRenderer;
}

Renderer& GraphicsModule::GetRenderer() noexcept
{
    return m_renderer;
}
    
const Renderer& GraphicsModule::GetRenderer() const noexcept
{
    return m_renderer;
}

} /* namespace tgon */
