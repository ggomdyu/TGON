/**
 * filename TMath.h
 * author   ggomdyu
 * since    03/14/2016
 * see      
 */

#pragma once
#include "../Platform/OSAL/PlatformInclude.h"
#include "Vector3.h"

#include <cmath>
#include <cstdint>


namespace tgon
{

class TGON_API Math
{
/** 
 * Ctor/Dtor
 */ 
public:
	Math( ) = delete;
	~Math( ) = delete;

/** 
 * Static variables
 */ 
public:
    static constexpr float PI = 3.141592654f;
    static constexpr float EPSILON = 0.0001f;
    static constexpr float Deg2Rad = PI / 180;
    static constexpr float Rad2Deg = 180 / PI;

/**
 * Commands
 */ 
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );

	/* @return	Discarded fractional parts */
	static float Floor( float val );

	/* @return	Discarded fractional parts */
	static int32_t FloorToInt( float val );

	/* @return	Square root value */
	static float Sqrt( float value );

	/* @return	Maximum value between first and second */
	template <class Ty>
	static constexpr Ty Max( Ty first, Ty second );

	/* @return	Minimum value between first and second */
	template <class Ty>
	static constexpr Ty Min( Ty first, Ty second );

	/* @return	Absolute value */
	template <class Ty>
	static constexpr Ty Abs( Ty value );

	/* @return	If value is over 0, then 1, else it's below, then -1, else 0 */
	template<class Ty>
	static constexpr Ty Sign( Ty value );

	/* @return	Clamped value between min and max */
	template <class Ty>
	static constexpr Ty Clamp( Ty value, Ty min, Ty max );

	/**
	 * @param	str		Undecayed string ( e.g. "Text" )
	 * @return			x65599 Hash value
	 */
	template <std::size_t N>
	static uint32_t StringToHash( const char( &str )[N] );
	
	/**
	 * @param	str		Decayed string ( e.g. const char* = "Text"; )
	 * @return			x65599 x65599 Hash value
	 */
	static uint32_t StringToHash( const char* str, std::size_t length );

	/**
	 * @param	from	Interpolation start value
	 * @param	to		Interpolation end value
	 * @param	t		Elapsed time
	 * @return			Interpolated value 
	 */
	static constexpr float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	
	/**
	 * @param	a/b/c	Interpolate target
	 * @param	t		Elapsed time
	 * @return			Interpolated value
	 */
	static Vector3 Bezier( const Vector3& a, const Vector3& b, const Vector3& c, float t );

/**
 *  Private variables
 */
private:
	static uint32_t x65599Hash( const char* str, std::size_t length );
};

inline float Math::Round( float val )
{
	return static_cast<float>( RoundToInt( val ));
}

inline int32_t Math::RoundToInt( float val )
{
//#if TGON_SUPPORT_SSE2
//	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
//#else
	return static_cast<int32_t>( std::round( val ));
//#endif
}

inline float Math::Floor( float val )
{
	return static_cast<float>( FloorToInt( val ));
}

inline int32_t Math::FloorToInt(
	float val )
{
//#if TGON_SUPPORT_SSE2
//	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
//#else
	return static_cast<int32_t>( std::floor( val ));
//#endif
}

inline float Math::Sqrt( float val )
{
	return std::sqrt( val );
}

template <class Ty>
constexpr Ty Math::Max( Ty first, Ty second )
{
	return ( first >= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Min( Ty first, Ty second )
{
	return ( first <= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Abs( Ty value )
{
	return ( value < (Ty)(0)) ? -value : value;
}

template<class Ty>
constexpr Ty Math::Sign( Ty value )
{
	return ( value > (Ty)(0)) ? (Ty)(1) : ( value < (Ty)(0)) ? (Ty)(-1) : (Ty)(0);
}

template <class Ty>
constexpr Ty Math::Clamp( Ty value, Ty min, Ty max )
{
	return Math::Max( Math::Min( value, max ), min );
}

template<std::size_t N>
inline uint32_t Math::StringToHash( const char( &str )[N] )
{
	return x65599Hash( str, N );
}

inline uint32_t Math::StringToHash( const char* str, std::size_t length )
{
	return x65599Hash( str, length );
}

constexpr float Math::Lerp( float from, float to, float t )
{
	return from + (( to-from )*t );
}

inline float Math::Smoothstep( float from, float to, float t )
{
	t = Math::Clamp(( t-from )/( to-from ), 0.0f, 1.0f );
	return t*t*( 3.0f-( 2.0f*t ));
}

inline Vector3 Math::Bezier( const Vector3& a, const Vector3& b, const Vector3& c, float t )
{
	const float inv = 1.0f-t;
	return {( inv*inv*a )+( 2.0f*t*inv*b )+( t*t*c )};
}

inline uint32_t Math::x65599Hash( const char* str, std::size_t length )
{
    // Check for hash collisions.
#if defined( _DEBUG ) || defined( DEBUG )
    static std::map<std::string, std::size_t> hashCollisionChecker;

    auto iter = hashCollisionChecker.find( str );
    if ( iter != hashCollisionChecker.end( ))
    {
        // Has a collision occurred?
        if ( std::strcmp( iter->first.c_str( ), str ))
        {
            // TODO: USE Boost logger or Google log!!
            assert( false && "DANGEROUS WARNING! :: Hash collision occured!!!" );
        }
    }
    else
    {
        hashCollisionChecker.insert({ str, length });
    }
#endif

	uint32_t hash = 0;
	for ( uint32_t i = 0; i < length; ++i )
	{
		hash = 65599*hash + str[i];
	}

	return hash^( hash >> 16 );
}

} /* namespace tgon */