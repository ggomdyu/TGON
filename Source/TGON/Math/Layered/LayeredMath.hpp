#pragma once
#include "LayeredMath.h"

#include <cmath>
#include <cstring>


TGON_FORCEINLINE TGON_CONSTEXPR float tgon::LayeredMath::DegreeToRadian(
		float angle ) 
{
	return angle * ( PI / 180.0f );
}


TGON_FORCEINLINE TGON_CONSTEXPR float tgon::LayeredMath::RadianToDegree(
		float radian ) 
{
	return radian * ( 180.0f / PI );
}


TGON_FORCEINLINE TGON_CONSTEXPR float tgon::LayeredMath::Lerp(
		const float from,
		const float to,
		const float t ) 
{
	return from + (( to-from )*t );
}


inline float tgon::LayeredMath::Smoothstep(
		const float from,
		const float to,
		const float t ) 
{
	const float _t = LayeredMath::Clamp(( t-from )/( to-from ),
											0.0f,
											1.0f );
	return _t*_t*( 3-2*_t );
}


template<class T>
TGON_CONSTEXPR T tgon::LayeredMath::Max(
		const T first,
		const T second ) 
{
	return ( first >= second ) ? first : second;
}


template<class T>
TGON_FORCEINLINE TGON_CONSTEXPR T tgon::LayeredMath::Min(
		const T first,
		const T second ) 
{
	return ( first <= second ) ? first : second;
}

template<class T>
TGON_FORCEINLINE TGON_CONSTEXPR T tgon::LayeredMath::Clamp(
		const T value,
		const T min,
		const T max ) 
{
	return LayeredMath::Max(
				LayeredMath::Min( value, max ),
				min
			);
}


TGON_FORCEINLINE float tgon::LayeredMath::Sqrt(
		float value ) 
{
	return std::sqrtf( value );
}


//template<class _Ty1, class _Ty2>
//inline static typename std::enable_if<std::is_arithmetic<_Ty1>::value && std::is_arithmetic<_Ty2>::value,
//	typename std::_Common_float_type<_Ty1, _Ty2>::type>::type
//		tgon::LayeredMath::Pow( const _Ty1 _Left, const _Ty2 _Right )
//{	
//	// bring mixed types to a common type
//	typedef typename std::_Common_float_type<_Ty1, _Ty2>::type type;
//	return ( ::pow( type( _Left ), type( _Right )));
//}


template<class T>
TGON_FORCEINLINE TGON_CONSTEXPR T tgon::LayeredMath::Abs(
		const T value ) 
{
	return ( value >= static_cast<T>( 0 )) ? value : -value;
}

TGON_FORCEINLINE float tgon::LayeredMath::FRand( ) 
{
	return WELLRNG512a( );
}


TGON_FORCEINLINE float tgon::LayeredMath::FRand(
		const float min,
		const float max ) 
{
	return min+( WELLRNG512a( )*( max-min ));
}


TGON_FORCEINLINE uint32_t tgon::LayeredMath::GenerateHash(
		const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}
