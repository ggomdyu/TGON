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

//SpriteBatch::SpriteBatch(const DrawPrimitive& drawPrimitive) :
//    m_drawPrimitives(1, drawPrimitive)
//{
//}
//
//void SpriteBatch::AddDrawPrimitive(const DrawPrimitive& drawPrimitive)
//{
//    m_drawPrimitives.push_back(drawPrimitive);
//}
//    
//bool SpriteBatch::CanBatch(const Sprite& sprite, const Material& material) const
//{
//    if (m_drawPrimitives.empty() == true)
//    {
//        return true;
//    }
//    else
//    {
//        const DrawPrimitive& drawPrimitive = m_drawPrimitives.back();
//
//        const Sprite& batchedSprite = *drawPrimitive.sprite;
//        const Material& batchedMaterial = *drawPrimitive.material;
//
//        return batchedSprite.IsScissorEnabled() == sprite.IsScissorEnabled() &&
//               batchedSprite.GetScissorRect() == sprite.GetScissorRect() &&
//               batchedMaterial->CanBatch(*sprite.GetMaterial());
//    }
//}
//    
//void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
//{
//    //m_material->Use();
//
//    for (auto& sprite : m_sprites)
//    {
//        // Set the world-view-projection matrix.
//        //m_material->SetWVP(drawPrimitive.matWorld * camera.GetViewProjectionMatrix());
//
//        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
//    }
//}
//
//std::vector<Sprite>& SpriteBatch::GetSprites() noexcept
//{
//    return m_sprites;
//}
//
//const std::vector<Sprite>& SpriteBatch::GetSprites() const noexcept
//{
//    return m_sprites;
//}
//
//SpriteBatchGroup::SpriteBatchGroup() :
//    m_quad(MeshUtility::GetSharedQuad())
//{
//}
//
//void SpriteBatchGroup::AddBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive)
//{
//    if (m_spriteBatches.empty())
//    {
//        m_spriteBatches.push_back(SpriteBatch(material, {drawPrimitive}));
//    }
//    else
//    {
//        SpriteBatch& backSpriteBatch = m_spriteBatches.back();
//        if (backSpriteBatch.CanBatch(material))
//        {
//            backSpriteBatch.AddDrawPrimitive(drawPrimitive);
//        }
//        else
//        {
//            m_spriteBatches.push_back(SpriteBatch(material, { drawPrimitive }));
//        }
//    }
//}
//
//void SpriteBatchGroup::AddBatch(const SpriteBatch& spriteBatch)
//{
//    m_spriteBatches.push_back(spriteBatch);
//}

//void SpriteBatchGroup::FlushBatch(Graphics& graphics, const Camera& camera)
//{
//    m_quad->Use();
//
//    for (auto& spriteBatch : m_spriteBatches)
//    {
//        spriteBatch.Draw(graphics, camera);
//    }
//
//    m_spriteBatches.clear();
//}

} /* namespace tgon */
