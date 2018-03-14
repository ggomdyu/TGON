/**
 * @filename    Cast.h
 * @author      ggomdyu
 * @since       05/24/2016
 */

#pragma once
#include <utility>

namespace tgon
{
namespace core
{
namespace detail
{

/**
 * @class   AutoCastProxy
 * @brief   Automatic type casting helper
 */
template <typename _CastFromType, typename _CastPolicyType>
struct AutoCastProxy final :
    public _CastPolicyType
{
/* @section Public constructor */
public:
    constexpr explicit AutoCastProxy(_CastFromType&& castFromPtr) noexcept :
        m_castFromPtr(castFromPtr)
    {
    }

/* @section Public operator */
public:
    template <typename _CastToType>
    constexpr operator _CastToType() const noexcept
    {
        return _CastPolicyType::template Cast<_CastFromType, _CastToType>(m_castFromPtr);
    }

/* @section Private variable */
private:
    _CastFromType m_castFromPtr;
};

struct SafeCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(_CastFromType&& castFromPtr) const noexcept
    {
        return static_cast<_CastToType>(std::forward<_CastFromType>(castFromPtr));
    }
};

struct ForceCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(_CastFromType&& castFromPtr) const noexcept
    {
        return reinterpret_cast<_CastToType>(std::forward<_CastFromType>(castFromPtr));
    }
};

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

} /* namespace core */
} /* namespace tgon */
