#include "AtlasTree.h"

namespace tgon
{
namespace
{

constexpr int32_t g_defaultTextureAtlasWidth;
constexpr int32_t g_defaultTextureAtlasHeight;

} /* namespace */

TextureAltasTreeNode::TextureAltasTreeNode(const I32Rect& rect) :
    rect(rect),
    id(0)
{
}

void TextureAltasTreeNode::Insert(const I32Rect& rect, int32_t id)
{
}

TextureAtlasTree::TextureAtlasTree() :
    m_rootNode(I32Rect(0, 0, g_defaultTextureAtlasWidth, g_defaultTextureAtlasHeight))
{
}

TextureAtlasTree::~TextureAtlasTree()
{
}

void TextureAtlasTree::Insert(const I32Rect& rect, int32_t id)
{
    m_rootNode.Insert(rect, id);
}

} /* namespace tgon */