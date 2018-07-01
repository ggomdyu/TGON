#include "PrecompiledHeader.h"

#include <cassert>

#include "../LowLevel/Graphics.h"
#include "../LowLevel/GraphicsType.h"
#include "../LowLevel/TextureType.h"

#include "SpriteBatch.h"
#include "Sprite.h"
#include "MeshUtility.h"

namespace tgon
{
    
Sprite::Sprite() :
    m_quad(MakeQuad(std::make_shared<TextureMaterial>()))
{
}

Sprite::Sprite(const std::string& filePath) :
    m_quad(MakeQuad(std::make_shared<TextureMaterial>(std::make_shared<Texture>(filePath, TextureProperty{}))))
{
}

Sprite::Sprite(std::shared_ptr<TextureMaterial> material) :
    m_quad(MakeQuad(material))
{
    assert(material != nullptr && "material can't be nullptr.");
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    material->SetTexture(texture);
}
    
std::shared_ptr<const Texture> Sprite::GetTexture() const noexcept
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    return material->GetTexture();
}

std::shared_ptr<Material> Sprite::GetMaterial() noexcept
{
    return m_quad->GetMaterial();
}

std::shared_ptr<const Material> Sprite::GetMaterial() const noexcept
{
    return m_quad->GetMaterial();
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
    
std::shared_ptr<Mesh> Sprite::GetMesh() noexcept
{
    return m_quad;
}
    
std::shared_ptr<const Mesh> Sprite::GetMesh() const noexcept
{
    return m_quad;
}

bool Sprite::CanBatch(Material* material) const
{
    return m_quad->GetMaterial()->CanBatch(*material);
}
    
void Sprite::Draw(Graphics& graphics)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_quad->GetMaterial().get());
    material->Use();
    material->GetShader()->SetParameterMatrix4fv("g_uMVP", m_matWVP[0]);

    m_quad->GetVertexBuffer()->Use();
    m_quad->GetIndexBuffer()->Use();

    graphics.DrawPrimitives(PrimitiveType::Triangles, 2);
}

} /* namespace tgon */
