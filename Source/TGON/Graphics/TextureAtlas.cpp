#include "PrecompiledHeader.h"

#include "TextureAtlas.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>

namespace tgon
{

TextureAtlas::TextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, bool isStaticAtlas, int32_t paddingOffset) :
    m_atlasTexture(nullptr, atlasSize, atlasPixelFormat, FilterMode::Bilinear, WrapMode::Clamp, false, !isStaticAtlas),
    m_context{},
    m_nodes{},
    m_paddingOffset(paddingOffset)
{
    stbrp_init_target(&m_context, atlasSize.width, atlasSize.height, m_nodes, std::extent<decltype(m_nodes)>::value);
}

bool TextureAtlas::Insert(const StringViewHash& name, const Image& image)
{
    stbrp_rect rect
    {
        static_cast<int>(m_packedImageInfos.size()), // id
        static_cast<stbrp_coord>(image.GetSize().width + m_paddingOffset), // w
        static_cast<stbrp_coord>(image.GetSize().height + m_paddingOffset), // h
        0, // x
        0, // y
        0 // was_packed
    };

    bool isPackingSucceed = stbrp_pack_rects(&m_context, &rect, 1) == 1;
    if (isPackingSucceed)
    {
        m_atlasTexture.SetData(image.GetImageData().get(), Vector2(rect.x, rect.y), image.GetSize(), m_atlasTexture.GetPixelFormat());
        m_packedImageInfos.insert({name.GetHashCode(), I32Rect(int32_t(rect.x), int32_t(rect.y), int32_t(rect.w), int32_t(rect.h))});
        return true;
    }
    
    return false;
}

bool TextureAtlas::Insert(const std::initializer_list<std::pair<StringViewHash, Image>>& imageDescs)
{
    for (int32_t i = 0; i < imageDescs.size(); ++i)
    {
        const auto& image = (imageDescs.begin() + i)->second;

        m_nodeRects[i] = stbrp_rect{
            i, // id
            static_cast<stbrp_coord>(image.GetSize().width + m_paddingOffset), // w
            static_cast<stbrp_coord>(image.GetSize().height + m_paddingOffset), // h
            0, // x
            0, // y
            0 // was_packed
        };
    }

    bool isPackingFailed = stbrp_pack_rects(&m_context, m_nodeRects, imageDescs.size()) != 0;
    if (isPackingFailed == false)
    {
        return false;
    }

    for (int32_t i = 0; i < imageDescs.size(); ++i)
    {
        const auto& imageDesc = imageDescs.begin() + i;
        m_packedImageInfos.insert({imageDesc->first.GetHashCode(), I32Rect(int32_t(m_nodeRects[i].x), int32_t(m_nodeRects[i].y), int32_t(m_nodeRects[i].w), int32_t(m_nodeRects[i].h))});
    }

    return true;
}

const I32Rect& TextureAtlas::GetImageRect(const StringViewHash& name) const
{
    return m_packedImageInfos[name.GetHashCode()];
}

int32_t TextureAtlas::GetTextureCount() const noexcept
{
    return m_packedImageInfos.size();
}

int32_t TextureAtlas::GetPaddingOffset() const noexcept
{
    return m_paddingOffset;
}

const Texture& TextureAtlas::GetAtlasTexture() const noexcept
{
    return m_atlasTexture;
}

const I32Extent2D& TextureAtlas::GetAtlasSize() const noexcept
{
    return m_atlasTexture.GetSize();
}

} /* namespace tgon */
