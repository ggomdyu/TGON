/**
 * @filename    COMPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 */

#pragma once

namespace tgon
{
namespace core
{

/**
 * @class   COMPtr
 * @brief   Manages reference count of COM object.
 */
template <typename _PointerType>
class COMPtr final
{
/* @section Public type */
public:
    using PointerType = _PointerType;

/* @section Public constructor */
public:
    constexpr COMPtr() noexcept;
    explicit COMPtr(_PointerType* rhs);
    COMPtr(const COMPtr& rhs);
    COMPtr(COMPtr&& rhs);
    ~COMPtr();

/* @section Public operator */
public:
    COMPtr& operator=(const COMPtr& rhs);
    COMPtr& operator=(COMPtr&& rhs);
    const _PointerType* operator->() const noexcept;
    _PointerType* operator->() noexcept;
    const _PointerType** operator&() const noexcept;
    _PointerType** operator&() noexcept;
    operator const _PointerType*() const noexcept;
    operator _PointerType*() noexcept;
    operator bool() noexcept;
    bool operator==(const COMPtr& rhs) const noexcept;
    bool operator!=(const COMPtr& rhs) const noexcept;

/* @section Public method */
public:
    /* @brief   Replaces the managed pointer to ptr. */
    void Reset(_PointerType* ptr = nullptr);

    /* @brief   Releases the managed pointer. */
    void Release();

    /* @brief   Returns the managed pointer. */
    const _PointerType* Get() const noexcept;

    /* @brief   Returns the managed pointer. */
    _PointerType* Get() noexcept;

/* @section Private variable */
private:
    _PointerType* m_ptr;
};

template <typename _PointerType>
constexpr COMPtr<_PointerType>::COMPtr() noexcept :
    m_ptr(nullptr)
{
}

template <typename _PointerType>
inline COMPtr<_PointerType>::COMPtr(_PointerType* rhs) :
    m_ptr(rhs)
{
    if (m_ptr)
    {
        m_ptr->AddRef();
    }
}

template <typename _PointerType>
inline COMPtr<_PointerType>::~COMPtr()
{   
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template <typename _PointerType>
inline COMPtr<_PointerType>::COMPtr(const COMPtr& rhs) :
    m_ptr(rhs.m_ptr)
{
    if (m_ptr)
    {
        m_ptr->AddRef();
    }
}

template <typename _PointerType>
inline COMPtr<_PointerType>::COMPtr(COMPtr&& rhs)
{
    if (m_ptr == rhs.m_ptr)
    {
        return;
    }

    if (m_ptr)
    {
        m_ptr->Release();
    }

    m_ptr = rhs.m_ptr;
    rhs.m_ptr = nullptr;
}

template <typename _PointerType>
inline COMPtr<_PointerType>& COMPtr<_PointerType>::operator=(const COMPtr& rhs)
{
    if (m_ptr == rhs.m_ptr)
    {
        return *this;
    }

    if (m_ptr)
    {
        m_ptr->Release();
    }

    rhs.m_ptr->AddRef();
    m_ptr = rhs.m_ptr;

    return *this;
}

template <typename _PointerType>
inline COMPtr<_PointerType>& COMPtr<_PointerType>::operator=(COMPtr&& rhs)
{
    if (m_ptr == rhs.m_ptr)
    {
        return *this;
    }

    if (m_ptr)
    {
        m_ptr->Release();
    }

    m_ptr = rhs.m_ptr;
    rhs.m_ptr = nullptr;
    
    return *this;
}

template <typename _PointerType>
inline const _PointerType* COMPtr<_PointerType>::operator->() const noexcept
{
    return m_ptr;
}

template <typename _PointerType>
inline _PointerType* COMPtr<_PointerType>::operator->() noexcept
{
    return m_ptr;
}

template <typename _PointerType>
inline const _PointerType** COMPtr<_PointerType>::operator&() const noexcept
{
    return &m_ptr;
}

template <typename _PointerType>
inline _PointerType** COMPtr<_PointerType>::operator&() noexcept
{
    return &m_ptr;
}

template <typename _PointerType>
inline COMPtr<_PointerType>::operator const _PointerType*() const noexcept
{
    return m_ptr;
}

template <typename _PointerType>
inline COMPtr<_PointerType>::operator _PointerType*() noexcept
{
    return m_ptr;
}

template<typename _PointerType>
inline COMPtr<_PointerType>::operator bool() noexcept
{
    return m_ptr != nullptr;
}

template <typename _PointerType>
inline bool COMPtr<_PointerType>::operator==(const COMPtr& rhs) const noexcept
{
    return m_ptr == rhs.m_ptr;
}

template <typename _PointerType>
inline bool COMPtr<_PointerType>::operator!=(const COMPtr& rhs) const noexcept
{
    return m_ptr != rhs.m_ptr;
}

template <typename _PointerType>
inline void COMPtr<_PointerType>::Reset(_PointerType* ptr)
{
    if (m_ptr)
    {
        m_ptr->Release();
    }

    if (ptr)
    {
        ptr->AddRef();
    }

    m_ptr = ptr;
}

template <typename _PointerType>
inline void COMPtr<_PointerType>::Release()
{
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template <typename _PointerType>
inline const _PointerType* COMPtr<_PointerType>::Get() const noexcept
{
    return m_ptr;
}

template <typename _PointerType>
inline _PointerType* COMPtr<_PointerType>::Get() noexcept
{
    return m_ptr;
}

} /* namespace core */
} /* namespace tgon */