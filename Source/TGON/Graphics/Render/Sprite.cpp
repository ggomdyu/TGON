#include "PrecompiledHeader.h"

#include <cassert>

#include "../LowLevel/Graphics.h"
#include "../LowLevel/GraphicsType.h"
#include "../LowLevel/TextureType.h"
#include "../LowLevel/VertexBuffer.h"
#include "../LowLevel/IndexBuffer.h"

#include "SpriteBatch.h"
#include "Sprite.h"
#include "MeshUtility.h"

namespace tgon
{
    
Sprite::Sprite() :
    m_quad(MakeQuad()),
    m_blendColor()
{
}

Sprite::Sprite(const std::string& filePath) :
    m_quad(MakeQuad()),
    m_texture(std::make_shared<Texture>(filePath)),
    m_material(std::make_shared<TextureMaterial>(m_texture))
{
}
    
Sprite::Sprite(const std::string& filePath, const Color4f& blendColor) :
    m_texture(std::make_shared<Texture>(filePath)),
    m_material(std::make_shared<TextureMaterial>(m_texture)),
    m_blendColor(blendColor)
{
}
    
Sprite::Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material) :
    m_quad(MakeQuad()),
    m_texture(texture),
    m_material(material)
{
}
    
Sprite::Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material, const Color4f& blendColor) :
    m_quad(MakeQuad()),
    m_texture(texture),
    m_material(material),
    m_blendColor(blendColor)
{
}
    
void Sprite::SetBlendColor(const Color4f& blendColor)
{
    m_blendColor = blendColor;
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_material.get());
    material->SetTexture(texture);
}
    
const Color4f& Sprite::GetBlendColor() const noexcept
{
    return m_blendColor;
}
    
std::shared_ptr<Texture>& Sprite::GetTexture() noexcept
{
    return m_texture;
}
    
const std::shared_ptr<Texture>& Sprite::GetTexture() const noexcept
{
    return m_texture;
}

const std::shared_ptr<Material>& Sprite::GetMaterial() const noexcept
{
    return m_material;
}
    
void Sprite::SetWVP(const Matrix4x4& matWVP) noexcept
{
    m_matWVP = matWVP;
}

const Matrix4x4& Sprite::GetWVP() const noexcept
{
    return m_matWVP;
}
    
const std::shared_ptr<Mesh>& Sprite::GetMesh() const noexcept
{
    return m_quad;
}

void Sprite::Draw(Graphics& graphics)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_material.get());
    material->Use();
    material->GetShader()->SetParameterMatrix4fv("g_uMVP", m_matWVP[0]);
    material->SetWVP()
    material->SetBlendColor(m_blendColor);

    m_quad->GetVertexBuffer()->Use();
    m_quad->GetIndexBuffer()->Use();

    graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
}

} /* namespace tgon */
