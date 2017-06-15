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

/* @brief   The host of Cast policy class */
template <typename CastFromTy, typename CastPolicy>
class AutoCastHost final :
    public CastPolicy
{
/**
 * @section Ctor/Dtor
 */
public:
    explicit AutoCastHost(CastFromTy&& rhs) noexcept;
    ~AutoCastHost() = default;
};

template<typename CastFromTy, typename CastPolicy>
inline AutoCastHost<CastFromTy, CastPolicy>::AutoCastHost(CastFromTy&& rhs) noexcept :
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
    explicit SafeCastPolicy(CastFromTy&& rhs) noexcept;
    ~SafeCastPolicy() = default;

/**
 * @section Operator
 */
public:
	/* @note    Convert FromTy to ToTy */
	template <typename CastToTy>
    operator CastToTy() noexcept;

/**
 * @section Private variable
 */
private:
	CastFromTy m_fromPtr;
};

template<typename CastFromTy>
inline SafeCastPolicy<CastFromTy>::SafeCastPolicy(CastFromTy&& rhs) noexcept :
    m_fromPtr(std::forward<CastFromTy>(rhs))
{
}

template<typename CastFromTy>
template<typename CastToTy>
inline SafeCastPolicy<CastFromTy>::operator CastToTy() noexcept
{
	return static_cast<CastToTy>(std::forward<CastFromTy>(m_fromPtr));
}

template <typename CastFromTy>
class ForceCastPolicy
{
/**
 * @section Ctor/Dtor
 */
protected:
    explicit ForceCastPolicy(CastFromTy&& rhs) noexcept;
    ~ForceCastPolicy() = default;

/**
 * @section Operator
 */
public:
	/* @brief   Convert FromTy to ToTy */
	template <typename CastToTy>
    operator CastToTy() noexcept;

/**
 * @section Private variable
 */
private:
	CastFromTy m_fromPtr;
};

template<typename CastFromTy>
inline ForceCastPolicy<CastFromTy>::ForceCastPolicy(CastFromTy&& rhs) noexcept :
	m_fromPtr(std::forward<CastFromTy>(rhs))
{
}

template<typename CastFromTy>
template<typename CastToTy>
inline ForceCastPolicy<CastFromTy>::operator CastToTy() noexcept
{
	return reinterpret_cast<CastToTy>(std::forward<CastFromTy>(m_fromPtr));
}

} /*namespace detail*/

template <typename CastFromTy>
inline auto AutoCast(CastFromTy&& rhs) noexcept -> detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>
{
	return detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>(std::forward<CastFromTy>(rhs));
}

template <typename CastFromTy>
inline auto ForceAutoCast(CastFromTy&& rhs) noexcept -> detail::AutoCastHost<CastFromTy, detail::ForceCastPolicy<CastFromTy>>
{
	return detail::AutoCastHost<CastFromTy, detail::SafeCastPolicy<CastFromTy>>(std::forward<CastFromTy>(rhs));
}

} /* namespace utility */
} /* namespace tgon */
