/**
 * @file    TextureAtlas.h
 * @author  ggomdyu
 * @since   06/18/2019
 */

#pragma once
#include <unordered_map>
#include <optional>
#include <memory>
#include <stb/stb_rect_pack.h>

#include "Core/NonCopyable.h"
#include "Math/Rect.h"
#include "Math/Extent.h"

#include "Texture.h"

namespace tgon
{

template <typename _KeyType>
class BasicTextureAtlas :
    private NonCopyable
{
/**@section Constructor */
public:
    BasicTextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset = 2);
    BasicTextureAtlas(BasicTextureAtlas&& rhs) noexcept;

/**@section Operator */
public:
    BasicTextureAtlas& operator=(BasicTextureAtlas&& rhs) noexcept;

/**@section Method */
public:
    static std::optional<BasicTextureAtlas> Load(const std::string_view& path);
    bool Insert(_KeyType key, std::byte* imageData, const I32Extent2D& size);
    void Clear();
    bool Contains(_KeyType key);
    std::optional<std::reference_wrapper<FRect>> GetTextureRect(_KeyType key) const;
    int32_t GetTextureCount() const noexcept;
    int32_t GetPaddingOffset() const noexcept;
    std::shared_ptr<const Texture> GetAtlasTexture() const noexcept;
    std::shared_ptr<Texture> GetAtlasTexture() noexcept;

/**@section Variable */
private:
    std::shared_ptr<Texture> m_atlasTexture;
    stbrp_context m_context;
    std::array<stbrp_node, 4096> m_nodes;
    std::array<stbrp_rect, 4096> m_nodeRects;
    mutable std::unordered_map<_KeyType, FRect> m_packedTextureInfos;
    int32_t m_paddingOffset;
};

using TextureAtlas = BasicTextureAtlas<size_t>;
using I32TextureAtlas = BasicTextureAtlas<int32_t>;
using I64extureAtlas = BasicTextureAtlas<int64_t>;

template <typename _KeyType>
inline BasicTextureAtlas<_KeyType>::BasicTextureAtlas(const I32Extent2D& atlasSize, PixelFormat atlasPixelFormat, int32_t paddingOffset) :
    m_atlasTexture(std::make_shared<Texture>(nullptr, atlasSize, atlasPixelFormat, FilterMode::Bilinear, WrapMode::Clamp, false, true)),
    m_context(std::make_unique<stbrp_context>()),
    m_nodes(std::make_unique<stbrp_node[]>(4096)),
    m_nodeRects(std::make_unique<stbrp_rect[]>(4096)),
    m_paddingOffset(paddingOffset)
{
    stbrp_init_target(m_context.get(), atlasSize.width, atlasSize.height, m_nodes.get(), 4096);
}

template <typename _KeyType>
inline BasicTextureAtlas<_KeyType>::BasicTextureAtlas(BasicTextureAtlas&& rhs) noexcept :
    m_atlasTexture(std::move(rhs.m_atlasTexture)),
    m_context(std::move(rhs.m_context)),
    m_nodes(std::move(rhs.m_nodes)),
    m_nodeRects(std::move(rhs.m_nodeRects)),
    m_paddingOffset(rhs.m_paddingOffset)
{
    rhs.m_paddingOffset = 0;
}

template <typename _KeyType>
inline BasicTextureAtlas<_KeyType>& BasicTextureAtlas<_KeyType>::operator=(BasicTextureAtlas&& rhs) noexcept
{
    m_atlasTexture = std::move(rhs.m_atlasTexture);
    m_context = std::move(rhs.m_context);
    m_nodes = std::move(rhs.m_nodes);
    m_nodeRects = std::move(rhs.m_nodeRects);
    m_paddingOffset = rhs.m_paddingOffset;
    
    rhs.m_paddingOffset = 0;

    return *this;
}

template <typename _KeyType>
inline bool BasicTextureAtlas<_KeyType>::Insert(_KeyType key, std::byte* imageData, const I32Extent2D& size)
{
    stbrp_rect rect
    {
        static_cast<decltype(stbrp_rect::id)>(m_packedTextureInfos.size()),
        static_cast<decltype(stbrp_rect::w)>(size.width + m_paddingOffset),
        static_cast<decltype(stbrp_rect::h)>(size.height + m_paddingOffset),
        0,
        0,
        0
    };

    bool isPackingSucceed = stbrp_pack_rects(m_context.get(), &rect, 1) == 1;
    if (isPackingSucceed)
    {
        m_atlasTexture->SetData(imageData, Vector2(rect.x, rect.y), size, m_atlasTexture->GetPixelFormat());
        m_packedTextureInfos.emplace(key, FRect(float(rect.x), float(rect.y), float(rect.w - m_paddingOffset), float(rect.h - m_paddingOffset)));
        return true;
    }

    return false;
}

template<typename _KeyType>
inline void BasicTextureAtlas<_KeyType>::Clear()
{
    m_context(std::make_unique<stbrp_context>());
    m_context


    m_nodes(std::make_unique<stbrp_node[]>(4096));
    m_nodeRects(std::make_unique<stbrp_rect[]>(4096));
    m_paddingOffset(paddingOffset);
}

template <typename _KeyType>
inline bool BasicTextureAtlas<_KeyType>::Contains(_KeyType key)
{
    return m_packedTextureInfos.find(key) != m_packedTextureInfos.end();
}

template <typename _KeyType>
inline std::optional<std::reference_wrapper<FRect>> BasicTextureAtlas<_KeyType>::GetTextureRect(_KeyType key) const
{
    auto iter = m_packedTextureInfos.find(key);
    if (iter == m_packedTextureInfos.end())
    {
        return {};
    }
    
    return iter->second;
}

template <typename _KeyType>
inline int32_t BasicTextureAtlas<_KeyType>::GetTextureCount() const noexcept
{
    return static_cast<int32_t>(m_packedTextureInfos.size());
}

template <typename _KeyType>
inline int32_t BasicTextureAtlas<_KeyType>::GetPaddingOffset() const noexcept
{
    return m_paddingOffset;
}

template <typename _KeyType>
inline std::shared_ptr<const Texture> BasicTextureAtlas<_KeyType>::GetAtlasTexture() const noexcept
{
    return m_atlasTexture;
}

template <typename _KeyType>
inline std::shared_ptr<Texture> BasicTextureAtlas<_KeyType>::GetAtlasTexture() noexcept
{
    return m_atlasTexture;
}

} /* namespace tgon */
