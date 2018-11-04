#include "PrecompiledHeader.h"

#include <cassert>

#include "Graphics/LowLevel/Graphics.h"
#include "Graphics/LowLevel/GraphicsType.h"
#include "Graphics/LowLevel/TextureType.h"
#include "Graphics/LowLevel/VertexBuffer.h"
#include "Graphics/LowLevel/IndexBuffer.h"

#include "Sprite.h"

namespace tgon
{

Sprite::Sprite(const std::shared_ptr<Texture>& texture) :
    m_texture(texture)
{
}

Sprite::Sprite(Sprite&& rhs) :
    //m_originPoint(rhs.m_originPoint),
    //m_anchorPoint(rhs.m_anchorPoint),
    m_texture(std::move(rhs.m_texture))
{
    //m_originPoint = {};
    //m_anchorPoint = {};
}

//void Sprite::SetOriginPoint(const Vector2& originPoint) noexcept
//{
//    m_originPoint = originPoint;
//}
//
//void Sprite::SetAnchorPoint(const Vector2& anchorPoint) noexcept
//{
//    m_anchorPoint = anchorPoint;
//}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
}

//Vector2& Sprite::GetOriginPoint() noexcept
//{
//    return m_originPoint;
//}
//
//const Vector2& Sprite::GetOriginPoint() const noexcept
//{
//    return m_originPoint;
//}
//
//Vector2& Sprite::GetAnchorPoint() noexcept
//{
//    return m_anchorPoint;
//}
//
//const Vector2& Sprite::GetAnchorPoint() const noexcept
//{
//    return m_anchorPoint;
//}
   
std::shared_ptr<Texture>& Sprite::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> Sprite::GetTexture() const noexcept
{
    return m_texture;
}

//
//void Sprite::Draw(Graphics& graphics)
//{
//    TextureMaterial* material = static_cast<TextureMaterial*>(m_material.get());
//    material->Use();
//    material->GetShader()->SetParameterMatrix4fv("g_uWVP", m_matWVP[0]);
//    material->SetWVP()
//    material->SetBlendColor(m_blendColor);
//
//    m_quad->GetVertexBuffer()->Use();
//    m_quad->GetIndexBuffer()->Use();
//
//    graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
//}

} /* namespace tgon */
