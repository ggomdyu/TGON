#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"
#include "Graphics/VertexFormat.h"

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
    m_sortingLayers(1),
    m_mainCamera(CreateMainCamera(graphics->GetDisplayWindow()))
{
}

void UIRendererModule::Update()
{
    m_graphics->DisableDepthTest();

    this->UpdateCameras();
    this->UpdateSpriteBatches();
    
    m_spriteVertexBuffer.Use();
    m_spriteVertexBuffer.SetData(m_spriteVertices.data(), m_spriteVertices.size() * sizeof(m_spriteVertices[0]), false);

    this->Draw();
}

void UIRendererModule::Draw()
{
    m_graphics->ClearColorDepthBuffer();

    this->FlushSpriteBatches();

    m_graphics->SwapBuffer();
}

void UIRendererModule::AddPrimitive(const std::shared_ptr<UIElement>& element, SortingLayer sotringLayer, const Matrix4x4& matWorld)
{
    m_sortingLayers[sotringLayer].emplace_back(element, matWorld);
}

void UIRendererModule::AddSubCamera(const std::shared_ptr<Camera>& camera)
{
    m_subCameras.push_back(camera);
}

bool UIRendererModule::RemoveSubCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find(m_subCameras.begin(), m_subCameras.end(), camera);
    if (iter == m_subCameras.end())
    {
        return false;
    }
    
    m_subCameras.erase(iter);
    return true;
}

void UIRendererModule::SetMaxSortingLayer(SortingLayer maxSortingLayer)
{
    m_sortingLayers.resize(static_cast<size_t>(maxSortingLayer));
}

std::shared_ptr<Camera> UIRendererModule::CreateMainCamera(const std::shared_ptr<Window>& displayWindow)
{
    auto clientSize = displayWindow->GetClientSize();
    float halfWidth = static_cast<float>(clientSize.width) * 0.5f;
    float halfHeight = static_cast<float>(clientSize.height) * 0.5f;
    return std::make_shared<OrthographicCamera>(tgon::FRect(-halfWidth, -halfHeight, static_cast<float>(clientSize.width), static_cast<float>(clientSize.height)), -1.0f, 1024.0f);
}

void UIRendererModule::UpdateCameras()
{
    m_mainCamera->Update();

    for (auto& subCamera : m_subCameras)
    {
        subCamera->Update();
    }
}

void UIRendererModule::UpdateSpriteBatches()
{
    for (auto& sortingLayer : m_sortingLayers)
    {
        for (auto& primitive : sortingLayer)
        {
            primitive.first->GetBatches(&m_spriteBatches, primitive.second, &m_spriteVertices);
        }

        sortingLayer.clear();
    }
}

void UIRendererModule::FlushSpriteBatches()
{
    auto flushSpriteBatches = [&](const std::shared_ptr<Camera>& camera)
    {
#if DEBUG
        int32_t drawCall = 0;
#endif
        for (auto& spriteBatch : m_spriteBatches)
        {
            auto material = spriteBatch.GetMaterial();
            material->Use();
            material->SetParameterWVPMatrix4fv(camera->GetViewProjectionMatrix()[0]);

            spriteBatch.FlushBatch(*m_graphics);
#if DEBUG
            ++drawCall;
#endif
        }
#if DEBUG
//        Debug::WriteLine(std::string("DrawCall: ") + std::to_string(drawCall));
    #endif
    };

    flushSpriteBatches(m_mainCamera);

    for (auto& subCamera : m_subCameras)
    {
        flushSpriteBatches(subCamera);
    }

    m_spriteBatches.clear();
    m_spriteVertices.clear();
}

} /* namespace tgon */
