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
/**@section Type */
public:
    using TextureAtlasKey = uint64_t;

/**@section Constructor */
public:
    FontAtlas() = default;
    explicit FontAtlas(const std::shared_ptr<Font>& font);
    explicit FontAtlas(std::shared_ptr<Font>&& font);
    FontAtlas(FontAtlas&& rhs) noexcept;
        
/**@section Operator */
public:
    FontAtlas& operator=(FontAtlas&& rhs) noexcept;

/**@section Method */
public:
    void Initialize(const std::shared_ptr<Font>& font);
    void Initialize(std::shared_ptr<Font>&& font);
    std::optional<std::reference_wrapper<FRect>> GetTextureRect(char32_t ch, int32_t fontSize) const;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;
    const FontFace& GetFace(int32_t fontSize) const;
    const GlyphData& GetGlyphData(char32_t ch, int32_t fontSize) const;
    I32Vector2 GetKerning(char32_t lhs, char32_t rhs, int32_t fontSize) const;
    I32Extent2D GetCharSize(char32_t ch, int32_t fontSize);

private:
    static TextureAtlasKey CreateTextureAtlasKey(char32_t ch, int32_t fontSize) noexcept;
    
/**@section Variable */
private:
    std::shared_ptr<Font> m_font;
    mutable BasicTextureAtlas<TextureAtlasKey> m_textureAtlas;
};

} /* namespace tgon */
