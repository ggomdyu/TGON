#include "PrecompiledHeader.h"

#include "TextureAtlas.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>

namespace tgon
{

TextureAtlas::TextureAtlas(const I32Extent2D& atlasSize, int32_t paddingOffset) :
    m_context{},
    m_nodes{},
    m_paddingOffset(paddingOffset)
{
    stbrp_init_target(&m_context, atlasSize.width, atlasSize.height, m_nodes, std::extent<decltype(m_nodes)>::value);
}

bool TextureAtlas::Insert(const StringViewHash& name, const std::shared_ptr<Texture>& texture)
{
    stbrp_rect rect
    {
        m_textures.size(), // id
        texture->GetSize().width + m_paddingOffset, // w
        texture->GetSize().height + m_paddingOffset, // h
        0, // x
        0, // y
        0 // was_packed
    };

    bool isPackingSucceed = stbrp_pack_rects(&m_context, &rect, 1) == 1;
    if (isPackingSucceed)
    {
        m_textures.insert({name.GetHashCode(), {I32Rect(int32_t(rect.x), int32_t(rect.y), int32_t(rect.w), int32_t(rect.h)), texture}});
        return true;
    }
    
    return false;
}

bool TextureAtlas::Insert(const std::initializer_list<std::pair<StringViewHash, std::shared_ptr<Texture>>>& textureDescs)
{
    for (int32_t i = 0; i < textureDescs.size(); ++i)
    {
        const auto& texture = (textureDescs.begin() + i)->second;

        m_nodeRects[i] = stbrp_rect{
            i, // id
            texture->GetSize().width + m_paddingOffset, // w
            texture->GetSize().height + m_paddingOffset, // h
            0, // x
            0, // y
            0 // was_packed
        };
    }

    bool isPackingSucceed = stbrp_pack_rects(&m_context, m_nodeRects, textureDescs.size()) == 1;
    if (isPackingSucceed)
    {
        int32_t i = 0;
        return true;
    }

    for (int32_t i = 0; i < textureDescs.size(); ++i)
    {
        const auto& textureDesc = textureDescs.begin() + i;
        m_textures.insert({textureDesc->first.GetHashCode(), {I32Rect(int32_t(m_nodeRects[i].x), int32_t(m_nodeRects[i].y), int32_t(m_nodeRects[i].w), int32_t(m_nodeRects[i].h)), textureDesc->second}});
    }

    return false;
}

std::shared_ptr<const Texture> TextureAtlas::GetTexture(const StringViewHash& name) const
{
    return m_textures[name.GetHashCode()].texture;
}

std::shared_ptr<Texture> TextureAtlas::GetTexture(const StringViewHash& name)
{
    return m_textures[name.GetHashCode()].texture;
}

const I32Rect& TextureAtlas::GetTextureRect(const StringViewHash& name) const
{
    return m_textures[name.GetHashCode()].rect;
}

int32_t TextureAtlas::GetTextureCount() const noexcept
{
    return m_textures.size();
}

int32_t TextureAtlas::GetPaddingOffset() const noexcept
{
    return m_paddingOffset;
}

I32Extent2D TextureAtlas::GetAtlasSize() const noexcept
{
    return I32Extent2D(m_context.width, m_context.height);
}

} /* namespace tgon */
