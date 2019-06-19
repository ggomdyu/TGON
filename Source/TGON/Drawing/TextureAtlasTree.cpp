#include "PrecompiledHeader.h"

#include "TextureAtlasTree.h"

namespace tgon
{

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

        int32_t paddedImageWidth = image.width + m_paddingOffset;
        int32_t paddedImageHeight = image.height + m_paddingOffset;
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

TextureAtlasTree::TextureAtlasTree(const I32Extent2D& textureAtlasSize, int32_t paddingOffset) :
    m_rootNode(I32Rect(0, 0, textureAtlasSize.width, textureAtlasSize.height)),
    m_paddingOffset(paddingOffset)
{
}

bool TextureAtlasTree::Insert(const I32Rect& rect, int32_t id)
{
    return m_rootNode.Insert(rect, id) != nullptr;
}

} /* namespace tgon */
