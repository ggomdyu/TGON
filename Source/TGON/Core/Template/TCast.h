/**
 * filename TCast.h
 * author   ggomdyu
 * since    05/24/2016
 */

#pragma once
#include <utility>

namespace tgon
{

namespace auto_cast_detail
{

// Host class 
template <typename FromTy, typename CastModel>
class AutoCastProxy final :
	public CastModel
{
/**
 * Ctor/Dtor
 */
public:
	explicit AutoCastProxy(FromTy&& rhs) noexcept :
		CastModel(rhs)
	{
	}
};

// Policy classes 
template <typename FromTy>
class SafeCast
{
/**
 * @section Ctor/Dtor
 */
public:
	explicit SafeCast(FromTy&& rhs) noexcept :
		m_fromPtr(std::forward<FromTy>(rhs))
	{
	}

/**
 * @section Operators
 */
public:
	/* @note	Convert FromTy to ToTy */
	template <typename ToTy>
	operator ToTy() noexcept
	{
		return static_cast<ToTy>(std::forward<FromTy>(m_fromPtr));
	}

/**
 * Private variables
 */
private:
	FromTy&& m_fromPtr;
};
template <typename FromTy>
class UnsafeCast
{
/**
 * @section Ctor/Dtor
 */
public:
	explicit UnsafeCast(FromTy&& rhs) noexcept:
		m_fromPtr(std::forward<FromTy>(rhs))
	{
	}

/**
 * @section Operators
 */
public:
	/* @brief   Convert FromTy to ToTy */
	template <typename ToTy>
	operator ToTy() noexcept
	{
		return reinterpret_cast<ToTy>(std::forward<FromTy>(m_fromPtr));
	}

/**
 * @section Private variable
 */
private:
	FromTy&& m_fromPtr;
};

} /*namespace detail*/

template <typename FromTy>
auto_cast_detail::AutoCastProxy<FromTy, auto_cast_detail::SafeCast<FromTy>> auto_cast(FromTy&& rhs) noexcept
{
    // TODO: Not uniform?
	return auto_cast_detail::AutoCastProxy<FromTy, auto_cast_detail::SafeCast<FromTy>>(std::forward<FromTy>(rhs));
}

template <typename FromTy>
auto_cast_detail::AutoCastProxy<FromTy, auto_cast_detail::UnsafeCast<FromTy>> force_auto_cast(FromTy&& rhs) noexcept
{
	return auto_cast_detail::AutoCastProxy<FromTy, auto_cast_detail::UnsafeCast<FromTy>>(std::forward<FromTy>(rhs));
}

} /* namespace tgon */
