#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"
#include "Graphics/VertexFormat.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"

#include "UIRendererModule.h"

namespace tgon
{

UIRendererModule::UIRendererModule(const std::shared_ptr<Graphics>& graphics) noexcept :
    m_graphics(graphics),
    m_spriteVertexBuffer({
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Position, 3, VertexFormatType::Float, false, sizeof(V3F_C4F_T2F), offsetof(V3F_C4F_T2F, position)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::Color, 4, VertexFormatType::Float, true, sizeof(V3F_C4F_T2F), offsetof(V3F_C4F_T2F, color)),
        VertexBufferLayoutDescriptor(VertexAttributeIndex::UV, 2, VertexFormatType::Float, false, sizeof(V3F_C4F_T2F), offsetof(V3F_C4F_T2F, uv))
    }),
    m_sortingLayers(1)
{
    this->PrepareDefaultMaterials();
}

void UIRendererModule::Update()
{
    this->UpdateSpriteBatches();
    
    m_spriteVertexBuffer.Use();
    m_spriteVertexBuffer.SetData(m_spriteVertices.data(), m_spriteVertices.size() * sizeof(m_spriteVertices[0]), false);

    this->Draw();
}

void UIRendererModule::Draw()
{
    m_graphics->ClearColorDepthBuffer();

#ifndef NDEBUG
    if (m_cameraList.size() <= 0)
    {
        Debug::WriteLine("UIRendererModule has no camera but trying to draw.");
        return;
    }
#endif
    this->FlushSpriteBatches();

    m_graphics->SwapBuffer();
}

void UIRendererModule::AddUIElement(const std::shared_ptr<UIElement>& element, int32_t sotringLayer, const Matrix4x4& matWorld)
{
    auto& sortingLayer = m_sortingLayers[sotringLayer];
    sortingLayer.emplace_back(element, matWorld);
}

void UIRendererModule::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool UIRendererModule::RemoveCamera(const std::shared_ptr<Camera>& camera)
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

void UIRendererModule::SetMaxSortingLayer(int32_t maxSortingLayer) noexcept
{
    m_sortingLayers.resize(static_cast<size_t>(maxSortingLayer));
}

int32_t UIRendererModule::GetMaxSortingLayer() const noexcept
{
    return static_cast<int32_t>(m_sortingLayers.size());
}

std::shared_ptr<Graphics> UIRendererModule::GetGraphics() noexcept
{
    return m_graphics;
}

std::shared_ptr<const Graphics> UIRendererModule::GetGraphics() const noexcept
{
    return m_graphics;
}

void UIRendererModule::PrepareDefaultMaterials()
{
    m_uiMaterial = std::make_shared<Material>(g_positionColorUVVert, g_positionColorUVFrag);
}

void UIRendererModule::UpdateSpriteBatches()
{
    for (auto& sortingLayer : m_sortingLayers)
    {
        for (auto& primitive : sortingLayer)
        {
            primitive.first->GetBatches(&m_batches, primitive.second, &m_spriteVertices);
        }

        sortingLayer.clear();
    }
}

void UIRendererModule::FlushSpriteBatches()
{
    m_uiMaterial->Use();

    for (auto& camera : m_cameraList)
    {
        m_uiMaterial->GetShaderProgram().SetParameterWVPMatrix4fv(camera->GetViewProjectionMatrix()[0]);

#if DEBUG
        int32_t drawCall = 0;
#endif
        for (auto& batch : m_batches)
        {
            batch.FlushBatch(*m_graphics);
#if DEBUG
            ++drawCall;
#endif
        }

        m_batches.clear();
#if DEBUG
//        Debug::WriteLine(std::string("DrawCall: ") + std::to_string(drawCall));
#endif
    }

    m_spriteVertices.clear();
}

} /* namespace tgon */
