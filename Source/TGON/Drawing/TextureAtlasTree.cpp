#include "TextureAtlasTree.h"

namespace tgon
{
namespace
{

constexpr int32_t g_defaultTextureAtlasWidth = 1024;
constexpr int32_t g_defaultTextureAtlasHeight = 1024;

} /* namespace */

TextureAltasTreeNode::TextureAltasTreeNode(const I32Rect& rect) :
    rect(rect),
    id(0)
{
}

TextureAltasTreeNode* TextureAltasTreeNode::Insert(const I32Rect& image, int32_t id)
{
    bool isLeafNode = (left == nullptr && right == nullptr);
    if (isLeafNode)
    {
        bool isImageAlreadyAssigned = (this->id != 0);
        if (isImageAlreadyAssigned)
        {
            return nullptr;
        }

        bool isFitWithImage = rect.Intersect(image) == false;
        if (isFitWithImage == false)
        {
            return nullptr;
        }
        
        if (rect.width - image.width > rect.height - image.height)
        {
            left = std::make_unique<TextureAltasTreeNode>(I32Rect(rect.x, rect.y, image.width, rect.height));
            right = std::make_unique<TextureAltasTreeNode>(I32Rect(rect.x + image.width, rect.y, rect.width - image.width, rect.height));
        }
        else
        {
            left = std::make_unique<TextureAltasTreeNode>(I32Rect(rect.x, rect.y, rect.width, image.height));
            right = std::make_unique<TextureAltasTreeNode>(I32Rect(rect.x, rect.y + image.height, rect.width, rect.height - image.height));
        }
        
        left->id = id;
    }
    else
    {
        auto insertedNode = left->Insert(image, id);
        if (insertedNode == nullptr)
        {
            insertedNode = right->Insert( image, id );
        }

        return insertedNode;
    }
    
    return nullptr;
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
