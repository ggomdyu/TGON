/**
 * @file    Cast.h
 * @author  ggomdyu
 * @since   05/24/2016
 */

#pragma once
#include <utility>

namespace tgon
{

template <typename _CastFromType, typename _CastPolicyType>
struct AutoCaster final :
    private _CastPolicyType
{
/* @section Public constructor */
public:
    template <typename _CastFromType2>
    constexpr explicit AutoCaster(_CastFromType2&& castFromValue) noexcept;

/* @section Public operator */
public:
    template <typename _CastToType>
    constexpr operator _CastToType() const noexcept;

/* @section Private variable */
private:
    _CastFromType m_castFromValue;
};

template <typename _CastFromType, typename _CastPolicyType>
template <typename _CastFromType2>
constexpr AutoCaster<_CastFromType, _CastPolicyType>::AutoCaster(_CastFromType2&& castFromValue) noexcept :
    m_castFromValue(std::forward<_CastFromType2>(castFromValue))
{
}

template <typename _CastFromType, typename _CastPolicyType>
template <typename _CastToType>
constexpr AutoCaster<_CastFromType, _CastPolicyType>::operator _CastToType() const noexcept
{
    return _CastPolicyType::template Cast<_CastFromType, _CastToType>(m_castFromValue);
}

struct SafeCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(const _CastFromType& castFromValue) const noexcept;
};

template <typename _CastFromType, typename _CastToType>
constexpr _CastToType SafeCastPolicy::Cast(const _CastFromType& castFromValue) const noexcept
{
    return static_cast<_CastToType>(castFromValue);
}

struct ForceCastPolicy
{
/* @section Protected method */
protected:
    template <typename _CastFromType, typename _CastToType>
    constexpr _CastToType Cast(const _CastFromType& castFromValue) const noexcept;
};

template <typename _CastFromType, typename _CastToType>
constexpr _CastToType ForceCastPolicy::Cast(const _CastFromType& castFromValue) const noexcept
{
    return reinterpret_cast<_CastToType>(castFromValue);
}

template <typename _CastFromType>
using SafeAutoCaster = AutoCaster<_CastFromType, SafeCastPolicy>;

template <typename _CastFromType>
using ForceAutoCaster = AutoCaster<_CastFromType, ForceCastPolicy>;

template <typename _CastFromType>
constexpr SafeAutoCaster<_CastFromType> AutoCast(_CastFromType&& value) noexcept
{
	return SafeAutoCaster<_CastFromType>(std::forward<_CastFromType>(value));
}

template <typename _CastFromType>
constexpr ForceAutoCaster<_CastFromType> ForceAutoCast(_CastFromType&& value) noexcept
{
	return ForceAutoCaster<_CastFromType>(std::forward<_CastFromType>(value));
}

} /* namespace tgon */
