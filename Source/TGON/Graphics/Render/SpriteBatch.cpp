#include "PrecompiledHeader.h"

#include "Graphics/LowLevel/Graphics.h"

#include "Mesh.h"
#include "Camera.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "FVF.h"
#include "Material.h"
#include "MeshUtility.h"

namespace tgon
{
//    
//SpriteBatch::SpriteBatch() :
//    SpriteBatch(nullptr, nullptr, nullptr, nullptr)
//{
//}
//    
//SpriteBatch::SpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld) :
//    SpriteBatch(&blendColor, &sprite, &material, &matWorld)
//{
//}
//    
//SpriteBatch::SpriteBatch(const Color4f* blendColor, const std::shared_ptr<Sprite>* sprite, const std::shared_ptr<Material>* material, const Matrix4x4* matWorld) :
//    m_blendColor(blendColor),
//    m_sprite(sprite),
//    m_material(material),
//    m_matWorlds{matWorld}
//{
//}
//
//void SpriteBatch::AddWorldMatrix(const Matrix4x4& matWorld)
//{
//    m_matWorlds.push_back(&matWorld);
//}
//
//void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
//{
//    (*m_material)->Use();
//
//    for (const auto& matWorld : m_matWorlds)
//    {
//        (*m_material)->SetWVP((*matWorld) * camera.GetViewProjectionMatrix());
//
//        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
//    }
//}
//
//bool SpriteBatch::CanBatch(const SpriteBatch& spriteBatch) const
//{
//    return this->CanBatch(*spriteBatch.m_blendColor, *spriteBatch.m_sprite, *spriteBatch.m_material);
//}
//
//bool SpriteBatch::CanBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material) const
//{
//    return *m_blendColor == blendColor &&
//           (*m_sprite)->GetTexture() == sprite->GetTexture() && // TODO: This should be changed to comparing the id of resource!
//           (*m_material)->CanBatch(*material);
//}
//
//const Color4f& SpriteBatch::GetBlendColor() const noexcept
//{
//    return *m_blendColor;
//}
//
//std::shared_ptr<Sprite> SpriteBatch::GetSprite() noexcept
//{
//    return *m_sprite;
//}
//    
//std::shared_ptr<const Sprite> SpriteBatch::GetSprite() const noexcept
//{
//    return *m_sprite;
//}
//
//std::shared_ptr<Material> SpriteBatch::GetMaterial() noexcept
//{
//    return *m_material;
//}
//    
//std::shared_ptr<const Material> SpriteBatch::GetMaterial() const noexcept
//{
//    return *m_material;
//}
//    
} /* namespace tgon */
