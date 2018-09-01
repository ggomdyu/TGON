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
