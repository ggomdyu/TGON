/**
 * @file    SpriteBatch.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Core/Math/Rect.h"

namespace tgon
{

class Graphics;
class Texture;
class Sprite;
enum class BlendMode;

class TGON_API SpriteBatch final
{
/**@section Constructor */
public:
    SpriteBatch(const std::shared_ptr<Texture>& texture, BlendMode blendMode, const FRect& scissorRect, const FRect& textureRect) noexcept;
    
/**@section Method */
public:
    bool CanBatch(const Sprite& rhs) const noexcept;
    void Merge(const Sprite& rhs);

/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    BlendMode m_blendMode;
    FRect m_scissorRect;
    std::vector<float> m_vertices;
};

} /* namespace tgon */
