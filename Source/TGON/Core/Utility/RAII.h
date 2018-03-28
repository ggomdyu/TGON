/**
 * @filename    RAII.h
 * @author      ggomdyu
 * @since       03/11/2018
 */

#pragma once
#include <type_traits>

namespace tgon
{

template <typename _ResourceType>
class DefaultRAIITraits
{
public:
    /* @brief   Adds the reference count of managed resource. */
    void AddRef(_ResourceType& resource)
    {
    }

    /* @brief   Releases the managed resource. */
    void Release(_ResourceType& resource)
    {
        resource = nullptr;
    }

    constexpr const _ResourceType GetNullValue() noexcept
    {
        return nullptr;
    }
};

/**
 * @class   RAII
 * @brief   RAII object that manages the lifecycle of object.
 */
template <typename _ResourceType, typename _TraitsType = DefaultRAIITraits<_ResourceType>>
class RAII :
    private _TraitsType
{
/* @section Public type */
public:
    using ResourceType = _ResourceType;

/* @section Public constructor */
protected:
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

    /* @brief   Returns special value which indicates resource is null. */
    _ResourceType GetNullValue() const noexcept;

/* @section Protected variable */
protected:
    _ResourceType m_resource;
};

template <typename _ResourceType, typename _DerivedType>
constexpr RAII<_ResourceType, _DerivedType>::RAII() noexcept :
    m_resource(this->GetNullValue())
{
}

template <typename _ResourceType, typename _DerivedType>
constexpr RAII<_ResourceType, _DerivedType>::RAII(const _ResourceType& rhs) :
    m_resource(rhs)
{
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>::~RAII()
{   
    this->Release();
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>::RAII(const RAII& rhs) :
    m_resource(rhs.m_resource)
{
    this->AddRef();
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>::RAII(RAII&& rhs) :
    m_resource(std::move(rhs.m_resource))
{
    rhs.m_resource = this->GetNullValue();
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>& RAII<_ResourceType, _DerivedType>::operator=(const RAII& rhs)
{
    if (m_resource == rhs.m_resource)
    {
        return *this;
    }

    this->Release();

    new (this) RAII(rhs);

    return *this;
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>& RAII<_ResourceType, _DerivedType>::operator=(RAII&& rhs)
{
    if (m_resource == rhs.m_resource)
    {
        return;
    }

    this->Release();

    new (this) RAII(std::move(rhs));
    
    return *this;
}

template <typename _ResourceType, typename _DerivedType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline const _ResourceType& RAII<_ResourceType, _DerivedType>::operator->() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline _ResourceType& RAII<_ResourceType, _DerivedType>::operator->() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline const _ResourceType& RAII<_ResourceType, _DerivedType>::operator*() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
template <std::enable_if_t<std::is_pointer_v<_ResourceType>>*>
inline _ResourceType& RAII<_ResourceType, _DerivedType>::operator*() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline const _ResourceType* RAII<_ResourceType, _DerivedType>::operator&() const noexcept
{
    return &m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline _ResourceType* RAII<_ResourceType, _DerivedType>::operator&() noexcept
{
    return &m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>::operator const _ResourceType() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline RAII<_ResourceType, _DerivedType>::operator _ResourceType() noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline bool RAII<_ResourceType, _DerivedType>::operator==(const RAII& rhs) const noexcept
{
    return m_resource == rhs.m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline bool RAII<_ResourceType, _DerivedType>::operator!=(const RAII& rhs) const noexcept
{
    return m_resource != rhs.m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline void RAII<_ResourceType, _DerivedType>::AddRef()
{
    _TraitsType::AddRef(m_resource);
}

template <typename _ResourceType, typename _DerivedType>
inline void RAII<_ResourceType, _DerivedType>::Reset(const _ResourceType& resource)
{
    if (m_resource == resource)
    {
        return;
    }

    this->Release();

    m_resource = resource;
}

template <typename _ResourceType, typename _DerivedType>
inline void RAII<_ResourceType, _DerivedType>::Reset(_ResourceType&& resource)
{
    if (m_resource == resource)
    {
        return;
    }

    this->Release();

    m_resource = std::move(resource);
}

template <typename _ResourceType, typename _DerivedType>
inline void RAII<_ResourceType, _DerivedType>::Release()
{
    _TraitsType::Release(m_resource);
}

template <typename _ResourceType, typename _DerivedType>
inline const _ResourceType& RAII<_ResourceType, _DerivedType>::Get() const noexcept
{
    return m_resource;
}

template <typename _ResourceType, typename _DerivedType>
inline _ResourceType& RAII<_ResourceType, _DerivedType>::Get() noexcept
{
    return m_resource;
}

template<typename _ResourceType, typename _DerivedType>
inline _ResourceType RAII<_ResourceType, _DerivedType>::GetNullValue() const noexcept
{
    return _TraitsType::GetNullValue();
}

} /* namespace tgon */