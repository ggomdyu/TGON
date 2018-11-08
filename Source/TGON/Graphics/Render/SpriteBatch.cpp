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

SpriteBatch::SpriteBatch(const DrawPrimitive& drawPrimitive) :
    m_drawPrimitives(1, drawPrimitive)
{
}

void SpriteBatch::AddDrawPrimitive(const DrawPrimitive& drawPrimitive)
{
    m_drawPrimitives.push_back(drawPrimitive);
}

bool SpriteBatch::CanBatch(const DrawPrimitive& drawPrimitive) const
{
    if (m_drawPrimitives.empty() == true)
    {
        return true;
    }
    else
    {
        const DrawPrimitive& drawPrimitive2 = m_drawPrimitives.front();

        return drawPrimitive.isEnableScissorRect == drawPrimitive2.isEnableScissorRect &&
               drawPrimitive.scissorRect == drawPrimitive2.scissorRect &&
               drawPrimitive.blendColor == drawPrimitive2.blendColor &&
               drawPrimitive.material->CanBatch(*drawPrimitive2.material);
    }
}
    
void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
{
    if (m_drawPrimitives.empty())
    {
        return;
    }

    const auto& batchedDrawPrimitive = m_drawPrimitives.front();
    const auto& batchedMaterial = batchedDrawPrimitive.material;

    batchedMaterial->SetWVP(camera.GetViewProjectionMatrix());
    batchedMaterial->Use();

    if (batchedDrawPrimitive.isEnableScissorRect)
    {
        graphics.SetScissorRect(batchedDrawPrimitive.scissorRect);
        graphics.EnableScissorTest();
    }
    else
    {
        graphics.DisableScissorTest();
    }

    for (auto& drawPrimitive : m_drawPrimitives)
    {
        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
    }
}

std::vector<SpriteBatch::DrawPrimitive>& SpriteBatch::GetDrawPrimitives() noexcept
{
    return m_drawPrimitives;
}

const std::vector<SpriteBatch::DrawPrimitive>& SpriteBatch::GetDrawPrimitives() const noexcept
{
    return m_drawPrimitives;
}

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
