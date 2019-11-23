/**
 * @file    TextureAtlas.h
 * @author  ggomdyu
 * @since   06/18/2019
 * @see     http://blackpawn.com/texts/lightmaps/
 */

#pragma once
#include <unordered_map>
#include <optional>
#include <memory>
#include <stb/stb_rect_pack.h>

#include "Core/NonCopyable.h"
#include "Text/StringHash.h"
#include "Math/Rect.h"
#include "Math/Extent.h"

#include "Texture.h"

namespace tgon
{

class TextureAtlas :
    private NonCopyable
{
/**@section Constructor */
private:
    TextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset);
    TextureAtlas(TextureAtlas&& rhs) noexcept;

/**@section Operator */
public:
    TextureAtlas& operator=(TextureAtlas&& rhs);

/**@section Method */
public:
    static std::optional<TextureAtlas> Load(const std::string_view& path);
    static TextureAtlas Create(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset = 2);
    bool Insert(char32_t name, std::byte* imageData, const I32Extent2D& size);
    bool Insert(const StringViewHash& name, std::byte* imageData, const I32Extent2D& size);
    const I32Rect& GetTextureRect(char32_t name) const;
    const I32Rect& GetTextureRect(const StringViewHash& name) const;
    int32_t GetTextureCount() const noexcept;
    int32_t GetPaddingOffset() const noexcept;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;

private:
    bool Insert(size_t nameHashCode, std::byte* imageData, const I32Extent2D& size);

/**@section Variable */
private:
    std::shared_ptr<Texture> m_atlasTexture;
    std::unique_ptr<stbrp_context> m_context;
    std::unique_ptr<stbrp_node[]> m_nodes;
    std::unique_ptr<stbrp_rect[]> m_nodeRects;
    mutable std::unordered_map<size_t, I32Rect> m_packedTextureInfos;
    int32_t m_paddingOffset;
};

} /* namespace tgon */
