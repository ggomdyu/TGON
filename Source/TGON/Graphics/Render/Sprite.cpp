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
    m_quad(MakeQuad())
{
}

Sprite::Sprite(const std::string& filePath) :
    m_quad(MakeQuad()),
    m_texture(std::make_shared<Texture>(filePath)),
    m_material(std::make_shared<TextureMaterial>(m_texture))
{
}
    
Sprite::Sprite(const std::shared_ptr<Texture>& texture, const std::shared_ptr<Material>& material) :
    m_quad(MakeQuad()),
    m_texture(texture),
    m_material(material)
{
}

void Sprite::SetTexture(const std::shared_ptr<Texture>& texture)
{
    TextureMaterial* material = static_cast<TextureMaterial*>(m_material.get());
    material->SetTexture(texture);
}
    
const std::shared_ptr<Texture>& Sprite::GetTexture() const noexcept
{
    return m_texture;
}

const std::shared_ptr<Material>& Sprite::GetMaterial() const noexcept
{
    return m_material;
}
    
void Sprite::SetWorldViewProjectionMatrix(const Matrix4x4& matWVP) noexcept
{
    m_matWVP = matWVP;
}

const Matrix4x4& Sprite::GetWorldViewProjectionMatrix() const noexcept
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

    m_quad->GetVertexBuffer()->Use();
    m_quad->GetIndexBuffer()->Use();

    graphics.DrawIndexedPrimitives(PrimitiveType::Triangles, 2);
}

} /* namespace tgon */
