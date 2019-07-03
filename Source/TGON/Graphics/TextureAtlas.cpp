#include "PrecompiledHeader.h"

#include "TextureAtlas.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>

#include "String/Hash.h"

namespace tgon
{

TextureAtlas::TextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset) :
    m_atlasTexture(std::make_shared<Texture>(nullptr, atlasSize, atlasPixelFormat, FilterMode::Bilinear, WrapMode::Clamp, false, true)),
    m_context{},
    m_nodes{},
    m_paddingOffset(paddingOffset)
{
    stbrp_init_target(&m_context, atlasSize.width, atlasSize.height, m_nodes, std::extent<decltype(m_nodes)>::value);
}

bool TextureAtlas::Insert(UnicodeScalar name, const ImageView& image)
{
    return this->Insert(name.GetHashCode(), image);
}

bool TextureAtlas::Insert(const StringViewHash& name, const ImageView& image)
{
    return this->Insert(name.GetHashCode(), image);
}

bool TextureAtlas::Insert(const std::initializer_list<std::pair<UnicodeScalar, ImageView>>& imageDescs)
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

    bool isPackingFailed = stbrp_pack_rects(&m_context, m_nodeRects, static_cast<int>(imageDescs.size())) != 0;
    if (isPackingFailed == false)
    {
        return false;
    }

    for (int32_t i = 0; i < imageDescs.size(); ++i)
    {
        const auto& imageDesc = imageDescs.begin() + i;
        m_packedImageInfos.insert({imageDesc->first.GetHashCode(), I32Rect(int32_t(m_nodeRects[i].x), int32_t(m_nodeRects[i].y), int32_t(m_nodeRects[i].w - m_paddingOffset), int32_t(m_nodeRects[i].h - m_paddingOffset))});
    }

    return true;
}

bool TextureAtlas::Insert(const std::initializer_list<std::pair<StringViewHash, ImageView>>& imageDescs)
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

    bool isPackingFailed = stbrp_pack_rects(&m_context, m_nodeRects, static_cast<int>(imageDescs.size())) != 0;
    if (isPackingFailed == false)
    {
        return false;
    }

    for (int32_t i = 0; i < imageDescs.size(); ++i)
    {
        const auto& imageDesc = imageDescs.begin() + i;
        m_packedImageInfos.insert({imageDesc->first.GetHashCode(), I32Rect(int32_t(m_nodeRects[i].x), int32_t(m_nodeRects[i].y), int32_t(m_nodeRects[i].w - m_paddingOffset), int32_t(m_nodeRects[i].h - m_paddingOffset))});
    }

    return true;
}

const I32Rect& TextureAtlas::GetTextureRect(UnicodeScalar name) const
{
    return m_packedImageInfos[name.GetHashCode()];
}

const I32Rect& TextureAtlas::GetTextureRect(const StringViewHash& name) const
{
    return m_packedImageInfos[name.GetHashCode()];
}

int32_t TextureAtlas::GetTextureCount() const noexcept
{
    return static_cast<int32_t>(m_packedImageInfos.size());
}

int32_t TextureAtlas::GetPaddingOffset() const noexcept
{
    return m_paddingOffset;
}

std::shared_ptr<const Texture> TextureAtlas::GetAtlasTexture() const noexcept
{
    return m_atlasTexture;
}

std::shared_ptr<Texture> TextureAtlas::GetAtlasTexture() noexcept
{
    return m_atlasTexture;
}

bool TextureAtlas::Insert(size_t nameHashCode, const ImageView& image)
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
        m_atlasTexture->SetData(image.GetImageData(), Vector2(rect.x, rect.y), image.GetSize(), m_atlasTexture->GetPixelFormat());
        m_packedImageInfos.insert({nameHashCode, I32Rect(int32_t(rect.x), int32_t(rect.y), int32_t(rect.w - m_paddingOffset), int32_t(rect.h - m_paddingOffset))});
        return true;
    }

    return false;
}

} /* namespace tgon */
