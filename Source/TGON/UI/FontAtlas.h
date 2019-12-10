/**
 * @file    UIAtlasFont.h
 * @author  ggomdyu
 * @since   11/11/2019
 */

#pragma once
#include "Drawing/Font.h"
#include "Graphics/TextureAtlas.h"

namespace tgon
{

class FontAtlas
{
/**@section Constructor */
public:
    FontAtlas(const std::shared_ptr<Font>& font);
    FontAtlas(std::shared_ptr<Font>&& font);
    FontAtlas(FontAtlas&& rhs) noexcept;
        
/**@section Operator */
public:
    FontAtlas& operator=(FontAtlas&& rhs) noexcept;

/**@section Method */
public:
    std::optional<std::reference_wrapper<FRect>> GetTextureRect(char32_t ch, int32_t fontSize) const;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;
    const FontFace& GetFace(int32_t fontSize) const;
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetTextSize(int32_t fontSize);
    I32Extent2D GetTextSize(int32_t fontSize, const I32Extent2D& rect) const;

private:
    static uint64_t CreateTextureAtlasKey(char32_t ch, int32_t fontSize) noexcept;
    
/**@section Variable */
private:
    std::shared_ptr<Font> m_font;
    mutable BasicTextureAtlas<uint64_t> m_textureAtlas;
};

} /* namespace tgon */
