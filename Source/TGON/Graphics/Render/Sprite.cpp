#include "PrecompiledHeader.h"

#include <cassert>

#include "../LowLevel/Graphics.h"
#include "../LowLevel/GraphicsType.h"
#include "../LowLevel/TextureType.h"
#include "../LowLevel/VertexBuffer.h"
#include "../LowLevel/IndexBuffer.h"

#include "Sprite.h"
#include "Material.h"

namespace tgon
{

Sprite::Sprite(const std::string& filePath) :
    Sprite(std::make_shared<Texture>(filePath))
{
}
      
Sprite::Sprite(const std::shared_ptr<Texture>& texture) :
    m_texture(texture)
{
}

void Sprite::SetOriginPoint(const Vector2& originPoint)
{
    m_originPoint = originPoint;
}

Vector2& Sprite::GetOriginPoint() noexcept
{
    return m_originPoint;
}

const Vector2& Sprite::GetOriginPoint() const noexcept
{
    return m_originPoint;
}

void Sprite::SetAnchorPoint(const Vector2& anchorPoint)
{
    m_anchorPoint = anchorPoint;
}

Vector2& Sprite::GetAnchorPoint() noexcept
{
    return m_anchorPoint;
}

const Vector2& Sprite::GetAnchorPoint() const noexcept
{
    return m_anchorPoint;
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;
}
   
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
