/**
 * @file    TextureAtlas.h
 * @author  ggomdyu
 * @since   06/18/2019
 * @see     http://blackpawn.com/texts/lightmaps/
 */

#pragma once
#include <unordered_map>
#include <boost/noncopyable.hpp>
#include <stb/stb_rect_pack.h>

#include "String/UnicodeScalar.h"
#include "String/StringHash.h"
#include "Math/Rect.h"
#include "Math/Extent.h"

#include "Texture.h"

namespace tgon
{

class TGON_API TextureAtlas :
    private boost::noncopyable
{
/**@section Constructor */
public:
    TextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset = 2);

/**@section Method */
public:
    bool Insert(UnicodeScalar name, const ImageView& image);
    bool Insert(const StringViewHash& name, const ImageView& image);
    bool Insert(const std::initializer_list<std::pair<UnicodeScalar, ImageView>>& imageDescs);
    bool Insert(const std::initializer_list<std::pair<StringViewHash, ImageView>>& imageDescs);
    const I32Rect& GetTextureRect(UnicodeScalar name) const;
    const I32Rect& GetTextureRect(const StringViewHash& name) const;
    int32_t GetTextureCount() const noexcept;
    int32_t GetPaddingOffset() const noexcept;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;

private:
    bool Insert(size_t nameHashCode, const ImageView& image);

/**@section Variable */
private:
    std::shared_ptr<Texture> m_atlasTexture;
    stbrp_context m_context;
    stbrp_node m_nodes[4096];
    stbrp_rect m_nodeRects[std::extent<decltype(m_nodes)>::value];
    mutable std::unordered_map<size_t, I32Rect> m_packedImageInfos;
    int32_t m_paddingOffset;
};

} /* namespace tgon */
