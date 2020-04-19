#pragma once

#include <vector>

#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Math/Color.h"
#include "Math/Matrix4x4.h"

namespace tg
{

class UIBatch
{
/**@section Constructor */
public:
    UIBatch(const std::shared_ptr<Material>& material, const std::shared_ptr<Texture>& texture, BlendMode blendMode, int32_t vertexStartOffset) noexcept;
    
/**@section Method */
public:
    bool CanBatch(const UIBatch& rhs) const noexcept;
    void Merge(float x, float y, const FRect& textureRect, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices);
    void Merge(const FRect& textureRect, const FExtent2D& textureSize, const Vector2& pivot, const Color4f& blendColor, const Matrix4x4& matWorld, std::vector<float>* vertices);
    void FlushBatch(Graphics& graphics);
    std::shared_ptr<Material> GetMaterial() noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Material> GetMaterial() const noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    FilterMode GetFilterMode() const noexcept;
    BlendMode GetBlendMode() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<Texture> m_texture;
    BlendMode m_blendMode;
    int32_t m_vertexStartOffset;
    int32_t m_vertexEndOffset;
};

}
