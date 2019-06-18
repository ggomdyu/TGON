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
    TextureAltasNode* Insert(const I32Rect& rect, int32_t id);

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
    TextureAtlasTree();

/**@section Destructor */
public:
    virtual ~TextureAtlasTree();

/**@section Method */
public:
    bool Insert(const I32Rect& rect, int32_t id);

public:
    TextureAltasNode m_rootNode;
};

} /* namespace tgon */
