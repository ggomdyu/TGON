/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Platform/PlatformInclude.h"

#include "Vector3.h"

#include <cstdint>
#include <cmath>


namespace tgon
{


class TGON_API Math
{
	// 
	// Static variables
	// 
public:
	static constexpr float PI = 3.141592654f;
	static constexpr float EPSILON = 0.0001f;
	static constexpr float Deg2Rad = PI/180;
	static constexpr float Rad2Deg = 180/PI;

	// 
	// Commands
	// 
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );
	static float Floor( float val );
	static int32_t FloorToInt( float val );
	static float Sqrt( float val );

	/* @return	Return maximum value between first and second */
	template <class Ty>
	static constexpr Ty Max( Ty first, Ty second );

	/* @return	Return minimum value between first and second */
	template <class Ty>
	static constexpr Ty Min( Ty first, Ty second );

	/* @return	Return absolute value of 'value' */
	template <class Ty>
	static constexpr Ty Abs( Ty value );

	/* @return if value is over 0, then return 1, else it's below, then return -1, else return 0 */
	template<class Ty>
	static constexpr Ty Sign( Ty value );


	/* @return	Return clamped value between min and max */
	template <class Ty>
	static constexpr Ty Clamp( Ty value, Ty min, Ty max );

	static uint32_t StringToHash( const char* str );
	static uint32_t StringToHash( const char* str, int length );

	static constexpr float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static Vector3 Hermite( const Vector3& a, const Vector3& b, const Vector3& c, float t );

	// 
	// Ctor/Dtor
	// 
public:
	Math( ) = delete;
	virtual ~Math( ) = delete;

	//
	//  Private variables
	//
private:
	static uint32_t x65599Hash( const char* str, std::size_t length );
};


} /* namespace tgon */


#include "Mathf.inl"