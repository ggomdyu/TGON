#include "TextureAtlasTree.h"

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

TextureAltasTreeNode* TextureAltasTreeNode::Insert(const I32Rect& rect, int32_t id)
{
    bool isLeafNode = (left == nullptr && right == nullptr);
    if (isLeafNode)
    {
        bool isImageAlreadyAssigned = (this->id != 0);
        if (isImageAlreadyAssigned)
        {
            return nullptr;
        }

        bool isFitWithImage = this->rect.Intersect(rect) == false;
        if (isFitWithImage == false)
        {
            return nullptr;
        }

        this->
    }
    else
    {
        auto insertedNode = left->Insert(rect, id);
        if (insertedNode == nullptr)
        {
            insertedNode = right->Insert( rect, id );
        }

        return insertedNode;
    }
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