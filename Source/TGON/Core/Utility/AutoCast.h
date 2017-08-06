/**
 * @filename    AutoCast.h
 * @author      ggomdyu
 * @since       05/24/2016
 * @desc        Automatic type caster with no casting type specifier
 */

#pragma once
#include <utility>

namespace tgon
{
namespace utility
{
namespace detail
{

template <typename _CastFromType, typename _CastPolicyType>
struct AutoCastProxy final :
    public _CastPolicyType
{
/* @section Ctor/Dtor */
public:
    constexpr explicit AutoCastProxy(_CastFromType&& rhs) noexcept;

/* @section Operator */
public:
    template <typename _CastToType>
    constexpr operator _CastToType() const noexcept;

/* @section Private variable */
private:
    _CastFromType m_castFromPtr;
};

template <typename _CastFromType, typename _CastPolicyType>
template <typename _CastToType>
constexpr AutoCastProxy<_CastFromType, _CastPolicyType>::operator _CastToType() const noexcept
{
    return _CastPolicyType::template Cast<_CastFromType, _CastToType>(m_castFromPtr);
}

template<typename _CastFromType, typename _CastPolicyType>
constexpr AutoCastProxy<_CastFromType, _CastPolicyType>::AutoCastProxy(_CastFromType&& castFromPtr) noexcept :
    m_castFromPtr(castFromPtr)
{
}

struct SafeCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(_CastFromType&& castFromPtr) const noexcept;
};

template <typename _CastFromType, typename _CastToType>
constexpr _CastToType SafeCastPolicy::Cast(_CastFromType&& castFromPtr) const noexcept
{
    return static_cast<_CastToType>(std::forward<_CastFromType>(castFromPtr));
}

struct ForceCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(_CastFromType&& castFromPtr) const noexcept;
};

template <typename _CastFromType, typename _CastToType>
constexpr _CastToType ForceCastPolicy::Cast(_CastFromType&& castFromPtr) const noexcept
{
    return reinterpret_cast<_CastToType>(std::forward<_CastFromType>(castFromPtr));
}

} /* namespace detail */

template <typename _CastFromType>
constexpr detail::AutoCastProxy<_CastFromType, detail::SafeCastPolicy> AutoCast(_CastFromType&& rhs) noexcept
{
	return detail::AutoCastProxy<_CastFromType, detail::SafeCastPolicy>(std::forward<_CastFromType>(rhs));
}

template <typename _CastFromType>
constexpr detail::AutoCastProxy<_CastFromType, detail::ForceCastPolicy> ForceAutoCast(_CastFromType&& rhs) noexcept
{
	return detail::AutoCastProxy<_CastFromType, detail::ForceCastPolicy>(std::forward<_CastFromType>(rhs));
}

} /* namespace utility */
} /* namespace tgon */
