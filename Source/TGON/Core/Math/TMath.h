/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TVector3.h"
#include "../../Platform/Slate/PlatformProperty.h"
#include "../../Platform/Config/Build.h"



namespace tgon
{



class TGON_API TMath
{
public:
	static float PI;
	static float EPSILON;
	
public:
	/*
		General
	*/
	static float Round( float val );
	static int32_t RoundToInt( float val );
	static float Floor( float val );
	static int32_t FloorToInt( float val );
	static float Sqrt( float val );
	static float Deg2Rad( float degree );
	static float Rad2Deg( float radian );
	static float Max( float first, float second );
	static float Min( float first, float second );
	static float Abs( float val );
	static float Clamp( float val, float min, float max );

	/*
		Hashing
	*/
	template <std::size_t N>
	static uint32_t GenerateHash( const char( &str )[N] );
	static uint32_t GenerateHash( const char* str );

	/*
		Interpolation
	*/
	static float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static TVector3 Hermite( const TVector3& a, const TVector3& b, const TVector3& c, float t );


private:
	// x65599 Hasher
	static uint32_t x65599Hash( const char* str, size_t length );
};


}


inline float tgon::TMath::Round( float val )
{
	return static_cast<float>( RoundToInt( val ));
}

inline int32_t tgon::TMath::RoundToInt( float val )
{
#if TGON_SUPPORT_SSE
	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
#else
	return static_cast<int32_t>( std::round( val ));
#endif
}

inline float tgon::TMath::Floor( float val )
{
	return static_cast<float>( FloorToInt( val ));
}

inline int32_t tgon::TMath::FloorToInt( float val )
{
#if TGON_SUPPORT_SSE
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
#else
	return static_cast<int32_t>( std::floor( val ));
#endif
}

inline float tgon::TMath::Sqrt( float val )
{
	return std::sqrt( val );
}

inline float tgon::TMath::Deg2Rad( float degree )
{
	return degree*( PI / 180.f );
}

inline float tgon::TMath::Rad2Deg( float radian )
{
	return radian*( 180.f / PI );
}

inline float tgon::TMath::Max( float first, float second )
{
	return ( first >= second ) ? first : second;
}

inline float tgon::TMath::Min( float first, float second )
{
	return ( first <= second ) ? first : second;
}

inline float tgon::TMath::Abs( float val )
{
	return ( val < 0 ) ? -val : val;
}

inline float tgon::TMath::Clamp( float val, float min, float max )
{
	return TMath::Max( TMath::Min( val, max ), min );
}

template <std::size_t N>
inline uint32_t tgon::TMath::GenerateHash( const char( &str )[N] )
{
	return x65599Hash( str, N );
}

inline uint32_t tgon::TMath::GenerateHash( const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}

inline float tgon::TMath::Lerp( float from, float to, float t )
{
	return from + (( to-from )*t );
}

inline float tgon::TMath::Smoothstep( float from, float to, float t )
{
	t = TMath::Clamp(( t-from )/( to-from ), 
		0.f, 1.f );

	return t*t*( 3.f-( 2.f*t ));
}

inline tgon::TVector3 tgon::TMath::Hermite( 
	const TVector3& a, 
	const TVector3& b, 
	const TVector3& c, 
	float t )
{
	const float inv = 1.f - t;
	return {( inv*inv*a ) + ( 2*t*inv*b ) + ( t*t*c )};
}