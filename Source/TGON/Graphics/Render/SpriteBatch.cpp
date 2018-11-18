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
    
SpriteBatch::SpriteBatch() :
    SpriteBatch(nullptr, nullptr, nullptr, nullptr)
{
}
    
SpriteBatch::SpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld) :
    SpriteBatch(&blendColor, &sprite, &material, &matWorld)
{
}
    
SpriteBatch::SpriteBatch(const Color4f* blendColor, const std::shared_ptr<Sprite>* sprite, const std::shared_ptr<Material>* material, const Matrix4x4* matWorld) :
    m_blendColor(blendColor),
    m_sprite(sprite),
    m_material(material),
    m_matWorlds{matWorld}
{
}

void SpriteBatch::AddWorldMatrix(const Matrix4x4& matWorld)
{
    m_matWorlds.push_back(&matWorld);
}

void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
{
    (*m_material)->Use();

    for (const auto& matWorld : m_matWorlds)
    {
        (*m_material)->SetWVP((*matWorld) * camera.GetViewProjectionMatrix());

        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
    }
}

bool SpriteBatch::CanBatch(const SpriteBatch& spriteBatch) const
{
    return this->CanBatch(*spriteBatch.m_blendColor, *spriteBatch.m_sprite, *spriteBatch.m_material);
}

bool SpriteBatch::CanBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material) const
{
    return *m_blendColor == blendColor &&
           (*m_sprite)->GetTexture() == sprite->GetTexture() && // TODO: This should be changed to comparing the id of resource!
           (*m_material)->CanBatch(*material);
}

const Color4f& SpriteBatch::GetBlendColor() const noexcept
{
    return *m_blendColor;
}

const std::shared_ptr<Sprite>& SpriteBatch::GetSprite() const noexcept
{
    return *m_sprite;
}

const std::shared_ptr<Material>& SpriteBatch::GetMaterial() const noexcept
{
    return *m_material;
}

SpriteBatchGroup::SpriteBatchGroup() :
    m_quad(MeshUtility::GetSharedQuad())
{
}
    
void SpriteBatchGroup::AddSpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld)
{
    if (m_spriteBatches.empty() == false)
    {
        SpriteBatch& backSpriteBatch = m_spriteBatches.back();
        if (backSpriteBatch.CanBatch(blendColor, sprite, material))
        {
            backSpriteBatch.AddWorldMatrix(matWorld);
            return;
        }
    }
    
   m_spriteBatches.push_back(SpriteBatch(blendColor, sprite, material, matWorld));
}

const std::vector<SpriteBatch>& SpriteBatchGroup::GetSpriteBatches() const noexcept
{
    return m_spriteBatches;
}

void SpriteBatchGroup::FlushBatch(Graphics& graphics, const Camera& camera)
{
    m_quad->Use();

    for (auto& spriteBatch : m_spriteBatches)
    {
        spriteBatch.Draw(graphics, camera);
    }

    m_spriteBatches.clear();
}

} /* namespace tgon */
