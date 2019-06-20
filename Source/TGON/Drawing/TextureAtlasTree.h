/**
 * @file    AtlasTree.h
 * @author  ggomdyu
 * @since   06/18/2019
 * @see     http://blackpawn.com/texts/lightmaps/
 */

#pragma once
#include <unordered_map>
#include <memory>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Math/Rect.h"
#include "Math/Extent.h"

namespace tgon
{

struct TextureAltasNode :
    private boost::noncopyable
{
/**@section Constructor */
public:
    TextureAltasNode(const I32Rect& rect);

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
/**@section Constructor */
public:
    explicit TextureAtlasTree(const I32Extent2D& textureAtlasSize, int32_t paddingOffset = 2);

/**@section Method */
public:
    bool Insert(const I32Rect& rect, int32_t id);
    void Bake();
    int32_t GetPaddingOffset() const noexcept;

private:
    TextureAltasNode m_rootNode;
    int32_t m_paddingOffset;
};

} /* namespace tgon */
