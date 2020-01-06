/**
 * @file    UIElement.h
 * @author  ggomdyu
 * @since   11/20/2019
 */

#pragma once
#include <vector>

#include "Core/NonCopyable.h"

#include "UIBatch.h"

namespace tgon
{

class UIElement :
    private NonCopyable
{
/**@section Destructor */
public:
    virtual ~UIElement() = default;
    
/**@section Method */
public:
    virtual void GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const = 0;
    void SetScissorRect(const FRect& rect) noexcept;
    const FRect& GetScissorRect() const noexcept;
    void EnableScissorRect() noexcept;
    void DisableScissorRect() noexcept;
    bool IsEnableScissorRect() const noexcept;

/**@section Variable */
protected:
    bool m_enableScissorRect = false;
    FRect m_scissorRect;
};

} /* namespace tgon */
