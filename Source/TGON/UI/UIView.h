/**
 * @file    UIView.h
 * @author  ggomdyu
 * @since   11/20/2019
 */

#pragma once
#include "Math/Rect.h"

namespace tgon
{

class UIView
{
/**@section Method */
public:
    void SetFrame(const I32Rect& frame) noexcept;
    void SetBounds(const I32Rect& bounds) noexcept;
    const I32Rect& GetFrame() const noexcept;
    const I32Rect& GetBounds() const noexcept;
    
/**@section Variable */
private:
    I32Rect m_frame;
    I32Rect m_bounds;
};

} /* namespace tgon */
