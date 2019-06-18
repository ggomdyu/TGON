/**
 * @file    AtlasTree.h
 * @author  ggomdyu
 * @since   06/18/2019
 */

#pragma once
#include <unordered_map>
#include <memory>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Math/Rect.h"

namespace tgon
{

struct TextureAltasTreeNode :
    private boost::noncopyable
{
/**@section Constructor */
public:
    TextureAltasTreeNode(const I32Rect& rect);

/**@section Method */
public:
    TextureAltasTreeNode* Insert(const I32Rect& rect, int32_t id);

/**@section Variable */
public:
    I32Rect rect;
    int id;
    std::unique_ptr<TextureAltasTreeNode> left;
    std::unique_ptr<TextureAltasTreeNode> right;
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
    void Insert(const I32Rect& rect, int32_t id);

private:
    TextureAltasTreeNode m_rootNode;
    //std::unordered_map<key, int32_t>
};

} /* namespace tgon */
