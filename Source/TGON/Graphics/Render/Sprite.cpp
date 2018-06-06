#include "PrecompiledHeader.h"

#include <cassert>

#include "../LowLevelRender/Graphics.h"

#include "SpriteBatch.h"
#include "Sprite.h"
#include "MeshUtility.h"

namespace tgon
{

Sprite::Sprite() noexcept :
    m_quad(MakeQuad(std::make_shared<TextureMaterial>()))
{
}

Sprite::Sprite(const std::shared_ptr<TextureMaterial>& material) noexcept :
    m_quad(MakeQuad(material))
{
    assert(material != nullptr && "material can't be nullptr.");
}

void Sprite::SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept
{
    m_matWVP = matWVP;
}

Matrix4x4& Sprite::GetWorldViewProjectionMatrix() noexcept
{
    return m_matWVP;
}

const Matrix4x4& Sprite::GetWorldViewProjectionMatrix() const noexcept
{
    return m_matWVP;
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    material->SetTexture(texture);
}

const std::shared_ptr<Texture>& Sprite::GetTexture() const noexcept
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    return material->GetTexture();
}

std::shared_ptr<TextureMaterial> Sprite::GetMaterial() noexcept
{
    return std::static_pointer_cast<TextureMaterial>(m_quad->GetMaterial());
}

std::shared_ptr<TextureMaterial> Sprite::GetMaterial() const noexcept
{
    return std::static_pointer_cast<TextureMaterial>(m_quad->GetMaterial());
}

void Sprite::Draw(GraphicsContext& context)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    material->Use();
    material->GetShader()->SetParameterMatrix4fv("g_uMVP", m_matWVP[0]);

    m_quad->GetVertexBuffer()->Use();
    m_quad->GetIndexBuffer()->Use();

    context.GetGraphics().DrawPrimitives(PrimitiveType::Triangles, 0, 2);
}

} /* namespace tgon */
