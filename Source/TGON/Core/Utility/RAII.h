/**
 * @filename    RAII.h
 * @author      ggomdyu
 * @since       03/11/2018
 */

#pragma once
#include <type_traits>

namespace tgon
{
namespace core
{

template <typename _ResourceType>
class DefaultRAIITraits
{
public:
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    static constexpr const _ResourceType GetNullValue() noexcept
    {
        return nullptr;
    }
};

/**
 * @class   RAII
 * @brief   RAII object that manages the lifecycle of object.
 */
template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType = DefaultRAIITraits<_ResourceType>>
class RAII
{
/* @section Public type */
public:
    using TraitsType = _TraitsType;
    using ResourceType = _ResourceType;

/* @section Public constructor */
public:
    constexpr RAII() noexcept;
    constexpr explicit RAII(const _ResourceType& rhs);
    RAII(const RAII& rhs);
    RAII(RAII&& rhs);
    ~RAII();

/* @section Public operator */
public:
    RAII& operator=(const RAII& rhs);
    RAII& operator=(RAII&& rhs);
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    const _ResourceType& operator->() const noexcept;
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    _ResourceType& operator->() noexcept;
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    const _ResourceType& operator*() const noexcept;
    template <std::enable_if_t<std::is_pointer_v<_ResourceType>>* = nullptr>
    _ResourceType& operator*() noexcept;
    const _ResourceType* operator&() const noexcept;
    _ResourceType* operator&() noexcept;
    operator const _ResourceType() const noexcept;
    operator _ResourceType() noexcept;
    bool operator==(const RAII& rhs) const noexcept;
    bool operator!=(const RAII& rhs) const noexcept;

/* @section Public method */
public:
    /* @brief   Adds the reference count of managed resource. */
    void AddRef();

    /* @brief   Replaces the managed resource. */
    void Reset(const _ResourceType& resource);

    /* @brief   Replaces the managed resource. */
    void Reset(_ResourceType&& resource);

    /* @brief   Releases the managed resource. */
    void Release();

    /* @brief   Returns the managed resource. */
    const _ResourceType& Get() const noexcept;

    /* @brief   Returns the managed resource. */
    _ResourceType& Get() noexcept;

/* @section Protected variable */
protected:
    _ResourceType m_resource;
};

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
constexpr RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::RAII() noexcept :
    m_resource(_TraitsType::GetNullValue())
{
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
constexpr RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::RAII(const _ResourceType& rhs) :
    m_resource(rhs)
{
    this->AddRef();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::~RAII()
{   
    this->Release();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::RAII(const RAII& rhs) :
    m_resource(rhs.m_resource)
{
    this->AddRef();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::RAII(RAII&& rhs)
{
    m_resource = std::move(rhs.m_resource);
    rhs.m_resource = _TraitsType::GetNullValue();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator=(const RAII& rhs)
{
    if (m_resource == rhs.m_resource)
    {
        return *this;
    }

    this->Release();

    new (this) RAII(rhs);

    return *this;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator=(RAII&& rhs)
{
    if (m_resource == rhs.m_resource)
    {
        return;
    }

    this->Release();

    new (this) RAII(std::move(rhs));
    
    return *this;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline const _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator->() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator->() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline const _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator*() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator*() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline const _ResourceType* RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator&() const noexcept
{
    return &m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline _ResourceType* RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator&() noexcept
{
    return &m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator const _ResourceType() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator _ResourceType() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline bool RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator==(const RAII& rhs) const noexcept
{
    return m_resource == rhs.m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline bool RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::operator!=(const RAII& rhs) const noexcept
{
    return m_resource != rhs.m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline void RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::AddRef()
{
    reinterpret_cast<_DerivedRAIIType*>(this)->AddRef();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline void RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::Reset(const _ResourceType& resource)
{
    if (m_resource == resource)
    {
        return;
    }

    this->Release();

    m_resource = resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline void RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::Reset(_ResourceType&& resource)
{
    if (m_resource == resource)
    {
        return;
    }

    this->Release();

    m_resource = std::move(resource);
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline void RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::Release()
{
    reinterpret_cast<_DerivedRAIIType*>(this)->Release();
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline const _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::Get() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedRAIIType, typename _TraitsType>
inline _ResourceType& RAII<_ResourceType, _DerivedRAIIType, _TraitsType>::Get() noexcept
{
    return m_resource;
}

} /* namespace core */
} /* namespace tgon */