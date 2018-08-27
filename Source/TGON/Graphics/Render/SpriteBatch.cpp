#include "PrecompiledHeader.h"

#include "SpriteBatch.h"
#include "MeshUtility.h"
#include "FVF.h"

namespace tgon
{
    
SpriteBatch::SpriteBatch(const std::shared_ptr<Material>& material) :
    m_material(material)
{
}

SpriteBatch::SpriteBatch(const std::shared_ptr<Material>& material, const std::initializer_list<DrawPrimitive>& drawPrimitives) :
    m_material(material),
    m_drawPrimitives(drawPrimitives)
{
}

void SpriteBatch::AddDrawPrimitive(const std::shared_ptr<Mesh>& mesh, const I32Rect& textureSize, const Matrix4x4& matWVP)
{
    m_drawPrimitives.push_back(DrawPrimitive{textureSize, matWVP});
}

void SpriteBatch::AddDrawPrimitive(const DrawPrimitive& drawPrimitive)
{
    m_drawPrimitives.push_back(drawPrimitive);
}
    
bool SpriteBatch::CanBatch(const std::shared_ptr<Material>& material) const
{
    return m_material->CanBatch(*material);
}
    
void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
{
    m_material->Use();

    for (auto& drawPrimitive : m_drawPrimitives)
    {
        Matrix4x4 matWorldViewProj = Matrix4x4::Scale(drawPrimitive.textureSize.right, drawPrimitive.textureSize.bottom, 1.0f);
        
        matWorldViewProj *= drawPrimitive.matWorld;
        matWorldViewProj *= camera.GetViewProjectionMatrix();
        
        // Set the world-view-projection matrix.
        m_material->SetWVP(matWorldViewProj);

        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
    }
}

SpriteBatchGroup::SpriteBatchGroup() :
    m_quad(MeshUtility::CreateSharedQuad())
{
}

void SpriteBatchGroup::AddSpriteBatch(const std::shared_ptr<Material>& material, const SpriteBatch::DrawPrimitive& drawPrimitive)
{
    for (auto& spriteBatch : m_spriteBatches)
    {
        if (spriteBatch.CanBatch(material))
        {
            spriteBatch.AddDrawPrimitive(drawPrimitive);
            return;
        }
    }
    
    m_spriteBatches.push_back(SpriteBatch(material, {drawPrimitive}));
}

void SpriteBatchGroup::AddSpriteBatch(const SpriteBatch& spriteBatch)
{
    m_spriteBatches.push_back(spriteBatch);
}

void SpriteBatchGroup::FlushSpriteBatch(Graphics& graphics, const Camera& camera)
{
    m_quad->Use();

    for (auto& spriteBatch : m_spriteBatches)
    {
        spriteBatch.Draw(graphics, camera);
    }

    m_spriteBatches.clear();
}

} /* namespace tgon */
