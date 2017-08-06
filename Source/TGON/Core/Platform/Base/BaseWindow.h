/**
 * @filename    BaseWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @desc        Set of Platform-agnostic Window interface.
 */

#pragma once
#include <string>
#include <cstdint>
#include <boost/noncopyable.hpp>

#include "BaseWindowType.h"

#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

template <typename _DerivedType>
class TGON_API BaseWindow
{
/* @section Ctor/Dtor */
public:
    BaseWindow();
    ~BaseWindow();
    
/* @section Public method */
public:
    void Show();
    void Hide();
    void Quit();
    void Maximize();
    void Minimize();
    void BringToFront();

    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetCaptionTitle(const char* captionTitle);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetCaptionTitle(char* destCaptionTitle) const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsClosed() const noexcept;

/* @section Protected variable */
protected:
    bool m_isClosed;
};

template <typename _DerivedType>
inline BaseWindow<_DerivedType>::BaseWindow() :
    m_isClosed(false)
{
}

template <typename _DerivedType>
inline BaseWindow<_DerivedType>::~BaseWindow()
{
    m_isClosed = true;
    static_cast<_DerivedType*>(this)->~_DerivedType();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::Show()
{
    static_cast<_DerivedType*>(this)->Show();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::Hide()
{
    static_cast<_DerivedType*>(this)->Hide();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::Quit()
{
    static_cast<_DerivedType*>(this)->Quit();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::Maximize()
{
    static_cast<_DerivedType*>(this)->Maximize();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::Minimize()
{
    static_cast<_DerivedType*>(this)->Minimize();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::BringToFront()
{
    static_cast<_DerivedType*>(this)->BringToFront();
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::SetPosition(int32_t x, int32_t y)
{
    static_cast<_DerivedType*>(this)->SetPosition(x, y);
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::SetSize(int32_t width, int32_t height)
{
    static_cast<_DerivedType*>(this)->SetSize(width, height);
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::SetCaptionTitle(const char* captionTitle)
{
    static_cast<_DerivedType*>(this)->SetCaptionTitle(captionTitle);
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::GetPosition(int32_t* x, int32_t* y) const
{
    static_cast<_DerivedType*>(this)->GetPosition(x, y);
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::GetSize(int32_t* width, int32_t* height) const
{
    static_cast<_DerivedType*>(this)->GetSize(width, height);
}

template <typename _DerivedType>
inline void BaseWindow<_DerivedType>::GetCaptionTitle(char* destCaptionTitle) const
{
    static_cast<_DerivedType*>(this)->GetCaptionTitle(destCaptionTitle);
}

template <typename _DerivedType>
inline bool BaseWindow<_DerivedType>::HasCaption() const
{
    return static_cast<_DerivedType*>(this)->HasCaption();
}

template <typename _DerivedType>
inline bool BaseWindow<_DerivedType>::IsResizable() const
{
    return static_cast<_DerivedType*>(this)->IsResizable();
}

template <typename _DerivedType>
inline bool BaseWindow<_DerivedType>::IsMaximized() const
    {
        return static_cast<_DerivedType*>(this)->IsMaximized();
}

template <typename _DerivedType>
inline bool BaseWindow<_DerivedType>::IsMinimized() const
{
    return static_cast<_DerivedType*>(this)->IsMinimized();
}

template <typename _DerivedType>
inline bool BaseWindow<_DerivedType>::IsClosed() const noexcept
{
    return static_cast<_DerivedType*>(this)->IsClosed();
}

} /* namespace platform */
} /* namespace tgon */
