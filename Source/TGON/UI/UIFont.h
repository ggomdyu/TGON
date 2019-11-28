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

class UIFont
{
/**@section Constructor */
public:
    UIFont(Font&& font);
    UIFont(UIFont&& rhs) noexcept;
        
/**@section Operator */
public:
    UIFont& operator=(UIFont&& rhs) noexcept;

/**@section Method */
public:
    void Insert(char32_t ch, int32_t fontSize);
    void Insert(const gsl::span<char32_t>& characters, int32_t fontSize);
    std::optional<std::reference_wrapper<FRect>> GetTextureRect(size_t key) const;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;
    const FontFace& GetFace(int32_t fontSize) const;
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetTextSize(int32_t fontSize);
    I32Extent2D GetTextSize(int32_t fontSize, const I32Extent2D& rect) const;

/**@section Variable */
private:
    Font m_font;
    TextureAtlas m_textureAtlas;
};

} /* namespace tgon */
