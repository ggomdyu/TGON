/**
 * @filename    SharedComPtr.h
 * @author      ggomdyu
 * @since       05/17/2016
 * @desc        Manages reference count of COM object.
 */

#pragma once

namespace tgon
{

template <typename ComPtrTy>
class SharedComPtr final
{
/**
 * @section Ctor/Dtor
 */
public:
    SharedComPtr() noexcept;
    explicit SharedComPtr(ComPtrTy* rhs);
    SharedComPtr(const SharedComPtr& rhs);
    SharedComPtr(SharedComPtr&& rhs);
    ~SharedComPtr();

/**
 * @section Operator
 */
public:
    SharedComPtr& operator=(const SharedComPtr& rhs);
    SharedComPtr& operator=(SharedComPtr&& rhs);
    const ComPtrTy** operator&() const noexcept;
    ComPtrTy** operator&() noexcept;
    const ComPtrTy* operator->() const noexcept;
    ComPtrTy* operator->() noexcept;
    operator const ComPtrTy*() const noexcept;
    operator ComPtrTy*() noexcept;

    bool operator==(const SharedComPtr& rhs) const noexcept;
    bool operator!=(const SharedComPtr& rhs) const noexcept;

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
inline SharedComPtr<ComPtrTy>::SharedComPtr() noexcept :
    m_ptr(nullptr)
{
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::SharedComPtr(ComPtrTy* rhs) :
    m_ptr(rhs)
{
    if (m_ptr)
    {
        m_ptr->AddRef();
    }
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::~SharedComPtr()
{   
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::SharedComPtr(const SharedComPtr& rhs) :
    m_ptr(rhs.m_ptr)
{
    if (m_ptr)
    {
        m_ptr->AddRef();
    }
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::SharedComPtr(SharedComPtr&& rhs)
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
inline SharedComPtr<ComPtrTy>& SharedComPtr<ComPtrTy>::operator=(const SharedComPtr& rhs)
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

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>& SharedComPtr<ComPtrTy>::operator=(SharedComPtr&& rhs)
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
inline const ComPtrTy** SharedComPtr<ComPtrTy>::operator&() const noexcept
{
    return &m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy** SharedComPtr<ComPtrTy>::operator&() noexcept
{
    return &m_ptr;
}

template<typename ComPtrTy>
inline const ComPtrTy* SharedComPtr<ComPtrTy>::operator->() const noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy* SharedComPtr<ComPtrTy>::operator->() noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::operator const ComPtrTy*() const noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline SharedComPtr<ComPtrTy>::operator ComPtrTy*() noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline bool SharedComPtr<ComPtrTy>::operator==(const SharedComPtr& rhs) const noexcept
{
    return m_ptr == rhs.m_ptr;
}

template<typename ComPtrTy>
inline bool SharedComPtr<ComPtrTy>::operator!=(const SharedComPtr& rhs) const noexcept
{
    return m_ptr != rhs.m_ptr;
}

template<typename ComPtrTy>
inline void SharedComPtr<ComPtrTy>::Reset(ComPtrTy* ptr)
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
inline void SharedComPtr<ComPtrTy>::Release()
{
    if (m_ptr)
    {
        m_ptr->Release();
        m_ptr = nullptr;
    }
}

template<typename ComPtrTy>
inline const ComPtrTy* SharedComPtr<ComPtrTy>::Get() const noexcept
{
    return m_ptr;
}

template<typename ComPtrTy>
inline ComPtrTy* SharedComPtr<ComPtrTy>::Get() noexcept
{
    return m_ptr;
}

}