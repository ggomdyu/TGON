/**
 * @filename    AutoCast.h
 * @author      ggomdyu
 * @since       05/24/2016
 */

#pragma once
#include <utility>

namespace tgon
{
namespace utility
{
namespace detail
{

// CRTP 적용하는게 더 좋아보임.

template <typename CastFromTy, typename CastPolicy>
class AutoCastHost final :
    public CastPolicy
{
/**
 * @section Ctor/Dtor
 */
public:
    constexpr explicit AutoCastHost(CastFromTy&& rhs) noexcept;
};

template<typename CastFromTy, typename CastPolicy>
constexpr AutoCastHost<CastFromTy, CastPolicy>::AutoCastHost(CastFromTy&& rhs) noexcept :
    CastPolicy(rhs)
{
}

template <typename CastFromTy>
class SafeCastPolicy
{
/**
 * @section Ctor/Dtor
 */
protected:
    constexpr explicit SafeCastPolicy(CastFromTy&& rhs) noexcept;

/**
 * @section Operator
 */
public:
	/* @note    Convert FromTy to ToTy */
	template <typename CastToTy>
    constexpr operator CastToTy() noexcept;

/**
 * @section Private variable
 */
private:
	CastFromTy m_castFromPtr;
};

template<typename CastFromTy>
constexpr SafeCastPolicy<CastFromTy>::SafeCastPolicy(CastFromTy&& rhs) noexcept :
    m_castFromPtr(std::forward<CastFromTy>(rhs))
{
}

template<typename CastFromTy>
template<typename CastToTy>
constexpr SafeCastPolicy<CastFromTy>::operator CastToTy() noexcept
{
	return static_cast<CastToTy>(std::forward<CastFromTy>(m_castFromPtr));
}

template <typename CastFromTy>
class ForceCastPolicy
{
/**
 * @section Ctor/Dtor
 */
protected:
    constexpr explicit ForceCastPolicy(CastFromTy&& rhs) noexcept;

/**
 * @section Operator
 */
public:
	/* @brief   Convert FromTy to ToTy */
	template <typename CastToTy>
    constexpr operator CastToTy() noexcept;

/**
 * @section Private variable
 */
private:
	CastFromTy m_castFromPtr;
};

template<typename CastFromTy>
constexpr ForceCastPolicy<CastFromTy>::ForceCastPolicy(CastFromTy&& rhs) noexcept :
	m_castFromPtr(std::forward<CastFromTy>(rhs))
{
}

template<typename CastFromTy>
template<typename CastToTy>
constexpr ForceCastPolicy<CastFromTy>::operator CastToTy() noexcept
{
	return reinterpret_cast<CastToTy>(std::forward<CastFromTy>(m_castFromPtr));
}

} /*namespace detail*/

template <typename CastFromTy>
constexpr auto AutoCast(CastFromTy&& rhs) noexcept -> detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>
{
	return detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>(std::forward<CastFromTy>(rhs));
}

template <typename CastFromTy>
constexpr auto ForceAutoCast(CastFromTy&& rhs) noexcept -> detail::AutoCastHost<CastFromTy, detail::ForceCastPolicy<CastFromTy>>
{
	return detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>(std::forward<CastFromTy>(rhs));
}

} /* namespace utility */
} /* namespace tgon */
