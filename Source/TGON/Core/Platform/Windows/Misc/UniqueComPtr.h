/**
 * @filename    UniqueComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 * @desc        Manages reference count of COM object.
 */

#pragma once
#include <cassert>

namespace tgon
{

template <typename ComPtrTy>
class UniqueComPtr final
{
/**
 * @section Ctor/Dtor
 */
public:
    UniqueComPtr() noexcept;
    UniqueComPtr(ComPtrTy* rhs);
    UniqueComPtr(const UniqueComPtr& rhs) = delete;
    UniqueComPtr(UniqueComPtr&& rhs);
    ~UniqueComPtr();

/**
 * @section Operator
 */
public:
    UniqueComPtr& operator=(const UniqueComPtr& rhs) = delete;
    UniqueComPtr& operator=(UniqueComPtr&& rhs);
    const ComPtrTy** operator&() const noexcept;
    ComPtrTy** operator&() noexcept;
    const ComPtrTy* operator->() const noexcept;
    ComPtrTy* operator->() noexcept;
    operator const ComPtrTy*() const noexcept;
    operator ComPtrTy*() noexcept;
    bool operator==(const UniqueComPtr& rhs) const noexcept;
    bool operator!=(const UniqueComPtr& rhs) const noexcept;

/**
 * @section Public command method
 */
public:
    /**
     * @brief           Sets new pointer
     * @param   ptr     A pointer you want to set
     */
    void Reset(ComPtrTy* ptr);

    /* @brief   Decreases reference count. */
    void Release();

/**
 * @section Get method
 */
public:
    const ComPtrTy* Get() const noexcept;
    ComPtrTy* Get() noexcept;

/**
 * @section Private variable
 */
private:
	ComPtrTy* m_ptr;
};

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::UniqueComPtr() noexcept :
    m_ptr(nullptr)
{
}

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::UniqueComPtr(ComPtrTy* rhs) :
    m_ptr(rhs)
{
    // TODO: 뭔가 이거 문제가 있어보임.
    if (rhs)
    {
        rhs->AddRef();
    }
}

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::UniqueComPtr(UniqueComPtr&& rhs)
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

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::~UniqueComPtr()
{
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>& UniqueComPtr<ComPtrTy>::operator=(UniqueComPtr&& rhs)
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

template<typename ComPtrTy>
inline const ComPtrTy** UniqueComPtr<ComPtrTy>::operator&() const noexcept
{
    return &m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy** UniqueComPtr<ComPtrTy>::operator&() noexcept
{
    return &m_ptr;
}

template<typename ComPtrTy>
inline const ComPtrTy* UniqueComPtr<ComPtrTy>::operator->() const noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy* UniqueComPtr<ComPtrTy>::operator->() noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::operator const ComPtrTy*() const noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline UniqueComPtr<ComPtrTy>::operator ComPtrTy*() noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline bool UniqueComPtr<ComPtrTy>::operator==(const UniqueComPtr& rhs) const noexcept
{
    return m_ptr == rhs.m_ptr;
}

template<typename ComPtrTy>
inline bool UniqueComPtr<ComPtrTy>::operator!=(const UniqueComPtr& rhs) const noexcept
{
    return m_ptr != rhs.m_ptr;
}

template<typename ComPtrTy>
inline void UniqueComPtr<ComPtrTy>::Reset(ComPtrTy* ptr)
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

template<typename ComPtrTy>
inline void UniqueComPtr<ComPtrTy>::Release()
{
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template<typename ComPtrTy>
inline const ComPtrTy* UniqueComPtr<ComPtrTy>::Get() const noexcept
{
	return m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy* UniqueComPtr<ComPtrTy>::Get() noexcept
{
    return m_ptr;
}

}