/*
* Author : Cha Junho
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
/*
	Public members
*/
	static constexpr float PI = 3.141592654f;
	static constexpr float EPSILON = 0.0001f;
	static constexpr float Deg2Rad = PI/180;
	static constexpr float Rad2Deg = 180/PI;

/*
	Commands
*/
	static float Round( float val );
	static int32_t RoundToInt( float val );
	static float Floor( float val );
	static int32_t FloorToInt( float val );
	static float Sqrt( float val );
	static float Max( float first, float second );
	static float Min( float first, float second );
	static float Abs( float val );
	static float Clamp( float val, float min, float max );
	static uint32_t GenerateHash( const char* str );
	static float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static TVector3 Hermite( const TVector3& a, const TVector3& b, const TVector3& c, float t );


/*
	Cons/Destructor
*/
	TMath( ) = delete;
	virtual ~TMath( ) = delete;


private:
	static uint32_t x65599Hash( const char* str, std::size_t length );
};


inline float TMath::Round( float val )
{
	return static_cast<float>( RoundToInt( val ));
}

inline int32_t TMath::RoundToInt( float val )
{
#if TGON_SUPPORT_SSE
	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
#else
	return static_cast<int32_t>( std::round( val ));
#endif
}

inline float TMath::Floor( float val )
{
	return static_cast<float>( FloorToInt( val ));
}

inline int32_t TMath::FloorToInt( float val )
{
#if TGON_SUPPORT_SSE
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
#else
	return static_cast<int32_t>( std::floor( val ));
#endif
}

inline float TMath::Sqrt( float val )
{
	return std::sqrt( val );
}

inline float TMath::Max( float first, float second )
{
	return ( first >= second ) ? first : second;
}

inline float TMath::Min( float first, float second )
{
	return ( first <= second ) ? first : second;
}

inline float TMath::Abs( float val )
{
	return ( val < 0 ) ? -val : val;
}

inline float TMath::Clamp( float val, float min, float max )
{
	return TMath::Max( TMath::Min( val, max ), min );
}

inline uint32_t TMath::GenerateHash( const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}

inline float TMath::Lerp( float from, float to, float t )
{
	return from + (( to-from )*t );
}

inline float TMath::Smoothstep( float from, float to, float t )
{
	t = TMath::Clamp(( t-from )/( to-from ), 
		0.f, 1.f );

	return t*t*( 3.f-( 2.f*t ));
}

inline TVector3 TMath::Hermite( 
	const TVector3& a, 
	const TVector3& b, 
	const TVector3& c, 
	float t )
{
	const float inv = 1.f - t;
	return {( inv*inv*a ) + ( 2*t*inv*b ) + ( t*t*c )};
}


}
