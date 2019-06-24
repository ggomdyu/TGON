/**
 * @file    TextureAtlasTree.h
 * @author  ggomdyu
 * @since   06/18/2019
 * @see     http://blackpawn.com/texts/lightmaps/
 */

#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Math/Rect.h"
#include "Math/Extent.h"

#include "Texture.h"

namespace tgon
{

struct TextureAltasNode :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit TextureAltasNode(const I32Rect& rect);

/**@section Method */
public:
    TextureAltasNode* Insert(const I32Rect& rect, int32_t paddingOffset, int32_t id);

private:
    bool IsLeafNode() const noexcept;

/**@section Variable */
public:
    I32Rect rect;
    int32_t id;
    std::unique_ptr<TextureAltasNode> left;
    std::unique_ptr<TextureAltasNode> right;
};

class TGON_API TextureAtlasTree :
    private boost::noncopyable
{
/**@section Type */
public:
    using ReferenceType = TextureAltasNode&;
    using ConstReferenceType = const TextureAltasNode&;
    using IteratorType = TextureAltasNode*;
    using ConstIteratorType = const TextureAltasNode*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/**@section Constructor */
public:
    TextureAtlasTree(const I32Extent2D& textureSize, int32_t paddingOffset);

/**@section Method */
public:
    bool Insert(const I32Rect& rect, int32_t id);
    //void Erase(const TextureAltasNode* node);
    int32_t GetPaddingOffset() const noexcept;
    const TextureAltasNode* GetRootNode() const noexcept;
    TextureAltasNode* GetRootNode() noexcept;
    IteratorType begin() noexcept;
    IteratorType end() noexcept;
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const noexcept;
    ReverseIteratorType rbegin() noexcept;
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType crbegin() const noexcept;
    ConstReverseIteratorType crend() const noexcept;

private:
    TextureAltasNode m_rootNode;
    std::unordered_map<int, TextureAltasNode*> m_nodes;
    int32_t m_paddingOffset;
};

} /* namespace tgon */
