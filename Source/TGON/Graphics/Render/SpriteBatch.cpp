#include "PrecompiledHeader.h"

#include "../LowLevel/Graphics.h"
#include "../LowLevel/GraphicsType.h"

#include "SpriteBatch.h"

namespace tgon
{
    
void SpriteBatch::AddSprite(const std::shared_ptr<Sprite>& newSprite)
{
    for (auto& batchedSprites : m_batchedSpritesLayer)
    {
        // The front element is guaranted to exist because the 'batchedSprites' has one sprite at least.
        auto& batchedSprite = batchedSprites.front();

        // If new sprite can batched with current sprite set, then add it into the sprite set.
        if (batchedSprite->GetMaterial()->CanBatch(*newSprite->GetMaterial()))
        {
            batchedSprites.push_back(newSprite);
            return;
        }
    }
    
    // If failed to insert the sprite into other sprite set, then create new one.
    m_batchedSpritesLayer.push_back({newSprite});
}
    
void SpriteBatch::FlushBatch(Graphics& graphics)
{
    if (m_batchedSpritesLayer.size() <= 0)
    {
        return;
    }

    auto& batchedSprites = m_batchedSpritesLayer.front();

    // The front element is guaranted to exist because the 'batchedSprites' has one sprite at least.
    auto mesh = batchedSprites.front()->GetMesh();
    {
        mesh->GetVertexBuffer()->Use();
        mesh->GetIndexBuffer()->Use();
    }
    
    for (auto& batchedSprites : m_batchedSpritesLayer)
    {
        TextureMaterial* material = static_cast<TextureMaterial*>(batchedSprites.front()->GetMaterial().get());
        material->Use();

        for (auto& batchedSprite : batchedSprites)
        {
            TextureMaterial* material = static_cast<TextureMaterial*>(batchedSprite->GetMaterial().get());
            material->GetShader()->SetParameterMatrix4fv("g_uMVP", batchedSprite->GetWorldViewProjectionMatrix()[0]);

            graphics.DrawPrimitives(PrimitiveType::Triangles, 0, 2);
        }
    }
    
    m_batchedSpritesLayer.clear();
}

} /* namespace tgon */
