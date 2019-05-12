/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Math/Rect.h"

#include "VertexBuffer.h"

namespace tgon
{

class Graphics;
class Texture;
class VertexBuffer;
class Material;
class Sprite;
enum class BlendMode;

class TGON_API SpriteBatch final
{
/**@section Constructor */
public:
    SpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, bool enableScissorRect, const FRect& scissorRect, const FRect& textureRect, int32_t vertexStartOffset) noexcept;
    
/**@section Method */
public:
    bool CanBatch(const Sprite& rhs) const noexcept;
    bool Merge(const Sprite& rhs, std::vector<float>* vertices);
    void FlushBatch(Graphics& graphics);
    
/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    BlendMode m_blendMode;
    bool m_enableScissorRect;
    FRect m_scissorRect;
    int32_t m_vertexStartOffset;
    int32_t m_vertexEndOffset;
};

} /* namespace tgon */
