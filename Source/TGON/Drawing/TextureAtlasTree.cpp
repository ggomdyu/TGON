#include "PrecompiledHeader.h"

#include "TextureAtlasTree.h"

namespace tgon
{
namespace
{

constexpr int32_t g_defaultTextureAtlasWidth = 1024;
constexpr int32_t g_defaultTextureAtlasHeight = 1024;
constexpr int32_t paddingOffset = 2;

} /* namespace */

TextureAltasNode::TextureAltasNode(const I32Rect& rect) :
    rect(rect),
    id(0)
{
}

TextureAltasNode* TextureAltasNode::Insert(const I32Rect& image, int32_t id)
{
    if (this->IsLeafNode())
    {
        bool isImageAlreadyAssigned = (this->id != 0);
        if (isImageAlreadyAssigned)
        {
            return nullptr;
        }

        int32_t paddedImageWidth = image.width + paddingOffset;
        int32_t paddedImageHeight = image.height + paddingOffset;
        if (rect.width < paddedImageWidth || rect.height < paddedImageHeight)
        {
            return nullptr;
        }
        
        if (rect.width == paddedImageWidth && rect.height == paddedImageHeight)
        {
            this->id = id;
            return this;
        }

        if (rect.width - paddedImageWidth > rect.height - paddedImageHeight)
        {
            left = std::make_unique<TextureAltasNode>(I32Rect(rect.x, rect.y, paddedImageWidth, rect.height));
            right = std::make_unique<TextureAltasNode>(I32Rect(rect.x + paddedImageWidth, rect.y, rect.width - paddedImageWidth, rect.height));
        }
        else
        {
            left = std::make_unique<TextureAltasNode>(I32Rect(rect.x, rect.y, rect.width, paddedImageHeight));
            right = std::make_unique<TextureAltasNode>(I32Rect(rect.x, rect.y + paddedImageHeight, rect.width, rect.height - paddedImageHeight));
        }
        
        return left->Insert(image, id);
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

bool TextureAltasNode::IsLeafNode() const noexcept
{
    return left == nullptr && right == nullptr;
}

TextureAtlasTree::TextureAtlasTree() :
    m_rootNode(I32Rect(0, 0, g_defaultTextureAtlasWidth, g_defaultTextureAtlasHeight))
{
}

TextureAtlasTree::~TextureAtlasTree()
{
}

bool TextureAtlasTree::Insert(const I32Rect& rect, int32_t id)
{
    return m_rootNode.Insert(rect, id) != nullptr;
}

} /* namespace tgon */
