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

//void SpriteBatch::AddDrawPrimitive(const DrawPrimitive& drawPrimitive)
//{
//    m_drawPrimitives.push_back(drawPrimitive);
//}

void SpriteBatch::AddWorldMatrix(const Matrix4x4& matWorld)
{
    m_worldMatrixes.push_back(matWorld);
}

bool SpriteBatch::CanBatch(const SpriteBatch& spriteBatch) const
{
    return m_scissorRect == spriteBatch.m_scissorRect &&
           m_blendColor == spriteBatch.m_blendColor &&
           m_sprite->GetTexture()->GetFilePath() == spriteBatch.m_sprite->GetTexture()->GetFilePath() &&
           m_material->CanBatch(*spriteBatch.m_material);
}
    
SpriteBatch::SpriteBatch(const FRect& scissorRect, const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material) :
    m_scissorRect(scissorRect),
    m_blendColor(blendColor),
    m_sprite(sprite),
    m_material(material)
{
}

void SpriteBatch::Draw(Graphics& graphics, const Camera& camera)
{
    if (m_drawPrimitives.empty())
    {
        return;
    }

    const auto& batchedDrawPrimitive = m_drawPrimitives.front();
    const auto& batchedMaterial = batchedDrawPrimitive.material;

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

    for (const auto& drawPrimitive : m_drawPrimitives)
    {
        batchedMaterial->SetWVP(drawPrimitive.matWorld * camera.GetViewProjectionMatrix());
        graphics.DrawPrimitives(PrimitiveType::TriangleFan, 4);
    }
}

const FRect& SpriteBatch::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

const Color4f& SpriteBatch::GetBlendColor() const noexcept
{
    return m_blendColor;
}

std::shared_ptr<Sprite>& SpriteBatch::GetSprite() noexcept
{
    return m_sprite;
}

std::shared_ptr<const Sprite> SpriteBatch::GetSprite() const noexcept
{
    return m_sprite;
}

std::shared_ptr<Material>& SpriteBatch::GetMaterial() noexcept
{
    return m_material;
}

std::shared_ptr<const Material> SpriteBatch::GetMaterial() const noexcept
{
    return m_material;
}

SpriteBatchGroup::SpriteBatchGroup() :
    m_quad(MeshUtility::GetSharedQuad())
{
}

void SpriteBatchGroup::AddSpriteBatch(const SpriteBatch& spriteBatch)
{
    if (m_spriteBatches.empty() == false)
    {
        SpriteBatch& batchedSpriteBatch = m_spriteBatches.back();
        if (batchedSpriteBatch.CanBatch(spriteBatch))
        {
            batchedSpriteBatch.AddWorldMatrix(spriteBatch);
            return;
        }
    }

    m_spriteBatches.push_back(SpriteBatch(drawPrimitive));
}

std::vector<SpriteBatch>& SpriteBatchGroup::GetSpriteBatches() noexcept
{
    return m_spriteBatches;
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
