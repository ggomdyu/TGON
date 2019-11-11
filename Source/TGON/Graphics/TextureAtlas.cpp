#include "PrecompiledHeader.h"

#include "TextureAtlas.h"

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>

namespace tgon
{

TextureAtlas::TextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset) :
    m_atlasTexture(std::make_shared<Texture>(nullptr, atlasSize, atlasPixelFormat, FilterMode::Bilinear, WrapMode::Clamp, false, true)),
    m_context(std::make_unique<stbrp_context>()),
    m_nodes(std::make_unique<stbrp_node[]>(4096)),
    m_nodeRects(std::make_unique<stbrp_rect[]>(4096)),
    m_paddingOffset(paddingOffset)
{
    stbrp_init_target(m_context.get(), atlasSize.width, atlasSize.height, m_nodes.get(), 4096);
}

TextureAtlas::TextureAtlas(TextureAtlas&& rhs) noexcept :
    m_atlasTexture(std::move(rhs.m_atlasTexture)),
    m_context(std::move(rhs.m_context)),
    m_nodes(std::move(rhs.m_nodes)),
    m_nodeRects(std::move(rhs.m_nodeRects)),
    m_paddingOffset(rhs.m_paddingOffset)
{
    rhs.m_paddingOffset = 0;
}

TextureAtlas& TextureAtlas::operator=(TextureAtlas&& rhs)
{
    m_atlasTexture = std::move(rhs.m_atlasTexture);
    m_context = std::move(rhs.m_context);
    m_nodes = std::move(rhs.m_nodes);
    m_nodeRects = std::move(rhs.m_nodeRects);
    m_paddingOffset = rhs.m_paddingOffset;
    
    rhs.m_paddingOffset = 0;

    return *this;
}

TextureAtlas TextureAtlas::Create(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset)
{
    return TextureAtlas(atlasSize, atlasPixelFormat, paddingOffset);
}

bool TextureAtlas::Insert(char32_t name, std::byte* imageData, const I32Extent2D& size)
{
    return this->Insert(X65599Hash(name), imageData, size);
}

bool TextureAtlas::Insert(const StringViewHash& name, std::byte* imageData, const I32Extent2D& size)
{
    return this->Insert(name.GetHashCode(), imageData, size);
}

const I32Rect& TextureAtlas::GetTextureRect(char32_t name) const
{
    return m_packedTextureInfos[X65599Hash(name)];
}

const I32Rect& TextureAtlas::GetTextureRect(const StringViewHash& name) const
{
    return m_packedTextureInfos[name.GetHashCode()];
}

int32_t TextureAtlas::GetTextureCount() const noexcept
{
    return static_cast<int32_t>(m_packedTextureInfos.size());
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

bool TextureAtlas::Insert(size_t nameHashCode, std::byte* imageData, const I32Extent2D& size)
{
    stbrp_rect rect
    {
        static_cast<int>(m_packedTextureInfos.size()), // id
        static_cast<stbrp_coord>(size.width + m_paddingOffset), // w
        static_cast<stbrp_coord>(size.height + m_paddingOffset), // h
        0, // x
        0, // y
        0 // was_packed
    };

    bool isPackingSucceed = stbrp_pack_rects(m_context.get(), &rect, 1) == 1;
    if (isPackingSucceed)
    {
        m_atlasTexture->SetData(imageData, Vector2(rect.x, rect.y), size, m_atlasTexture->GetPixelFormat());
        m_packedTextureInfos.insert({nameHashCode, I32Rect(int32_t(rect.x), int32_t(rect.y), int32_t(rect.w - m_paddingOffset), int32_t(rect.h - m_paddingOffset))});
        return true;
    }

    return false;
}

} /* namespace tgon */
