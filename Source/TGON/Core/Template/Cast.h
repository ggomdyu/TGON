/*
* Author : Cha Junho
* Date : 05/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <utility>


namespace tgon
{


namespace detail
{
/* Host class */
template <typename FromTy, typename CastModel>
class AutoCastProxy final :
	public CastModel
{
	//
	// Ctor/Dtor
	//
public:
	explicit AutoCastProxy( FromTy&& rhs ) noexcept :
		CastModel( rhs )
	{
	}
};

/* Policy classes */
template <typename FromTy>
class SafeCast
{
	//
	// Ctor/Dtor
	//
public:
	explicit SafeCast( FromTy&& rhs ) noexcept :
		m_fromPtr( std::forward<FromTy>( rhs ))
	{
	}

	//
	// Operators
	//
public:
	/* @note	Convert FromTy to ToTy */
	template <typename ToTy>
	operator ToTy( ) noexcept
	{
		return static_cast<ToTy>( std::forward<FromTy>( m_fromPtr ));
	}

	//
	// Private variables
	//
private:
	FromTy&& m_fromPtr;
};
template <typename FromTy>
class UnsafeCast
{
	//
	// Ctor/Dtor
	//
public:
	explicit UnsafeCast( FromTy&& rhs ) noexcept:
		m_fromPtr( std::forward<FromTy>( rhs ))
	{
	}

	//
	// Operators
	//
public:
	/* @note	Convert FromTy to ToTy */
	template <typename ToTy>
	operator ToTy( ) noexcept
	{
		return reinterpret_cast<ToTy>( std::forward<FromTy>( m_fromPtr ));
	}

	//
	// Private variables
	//
private:
	FromTy&& m_fromPtr;
};
} /*namespace detail*/


template <typename FromTy>
detail::AutoCastProxy<FromTy, detail::SafeCast<FromTy>> auto_cast( FromTy&& rhs ) noexcept
{
	return detail::AutoCastProxy<FromTy, detail::SafeCast<FromTy>>( 
		std::forward<FromTy>( rhs )
	);
}

template <typename FromTy>
detail::AutoCastProxy<FromTy, detail::UnsafeCast<FromTy>> force_auto_cast( FromTy&& rhs ) noexcept
{
	return detail::AutoCastProxy<FromTy, detail::UnsafeCast<FromTy>>( 
		std::forward<FromTy>( rhs )
	);
}


} /*namespace tgon*/
