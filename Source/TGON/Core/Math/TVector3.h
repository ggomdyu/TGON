/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Slate/PlatformProperty.h"
#include "../Platform/Config/Build.h"

// NOT support exactly now
#undef TGON_SUPPORT_SSE

namespace tgon
{


struct TGON_API TVector3
{
public:
	static TGON_API const TVector3 Forward;
	static TGON_API const TVector3 Back;
	static TGON_API const TVector3 Up;
	static TGON_API const TVector3 Down;
	static TGON_API const TVector3 Left;
	static TGON_API const TVector3 Right;
	static TGON_API const TVector3 One;
	static TGON_API const TVector3 Zero;

public:
    TVector3( );
	TVector3( float x, float y, float z );
#if TGON_SUPPORT_SSE
	explicit TVector3( __m128 rhs );
#endif

	static float Dot( const TVector3& a, const TVector3& b );
	static TVector3 Cross( const TVector3& a, const TVector3& b );
	float Length( ) const;
	float LengthSq( ) const;
	static float Angle( const TVector3& a, const TVector3& b );
	static float Distance( const TVector3& a, const TVector3& b );
	void Normalize( );
	void TransformCoord( const struct TMatrix4x4& );
	void TransformNormal( const struct TMatrix4x4& );


public:
    // Arithmetic operators
	TVector3 operator+( const TVector3& ) const;
	TVector3 operator-( const TVector3& ) const;
	TVector3 operator*( const TVector3& ) const;
	TVector3 operator*( float ) const;
	TVector3 operator/( float ) const;

	friend TVector3 operator*( float lhs, const TVector3& rhs )
	{
		return rhs*lhs;
	}

	// Unary operators
	TVector3 operator+( ) const;
	TVector3 operator-( ) const;

	// Compound assignment operators
	TVector3& operator+=( const TVector3& );
	TVector3& operator-=( const TVector3& );
	TVector3& operator*=( const TVector3& );
	TVector3& operator*=( float );
	TVector3& operator/=( float );

	// Comparison operators
	bool operator==( const TVector3& ) const;
	bool operator!=( const TVector3& ) const;

	float& operator[]( int32_t );
	float operator[]( int32_t ) const;
	

public:
#if TGON_SUPPORT_SSE
	__m128 reg;
#else
	float x, y, z;
#endif
};


inline TVector3::TVector3( ) :
#if TGON_SUPPORT_SSE
	reg( _mm_setzero_ps( ))
#else
	x( 0.f ),
	y( 0.f ),
	z( 0.f )
#endif
{
}

inline TVector3::TVector3( float x, float y, float z ) :
#if TGON_SUPPORT_SSE
	reg( _mm_setr_ps( x, y, z, 0.f ))
#else
	x( x ), 
	y( y ), 
	z( z )
#endif
{
}

inline TVector3 TVector3::operator+( 
	const TVector3& rhs ) const
{
#if TGON_SUPPORT_SSE
	return TVector3( _mm_add_ps( reg, rhs.reg ));
#else
	return TVector3( x+rhs.x, y+rhs.y, z+rhs.z );
#endif
}

inline TVector3 TVector3::operator-( 
	const TVector3& rhs ) const
{
#if TGON_SUPPORT_SSE
	return TVector3( _mm_sub_ps( reg, rhs.reg ));
#else
	return TVector3( x-rhs.x, y-rhs.y, z-rhs.z );
#endif
}

inline TVector3 TVector3::operator*(
	const TVector3& rhs ) const
{
#if TGON_SUPPORT_SSE
#else
	return TVector3( x*rhs.x, y*rhs.y, z*rhs.z );
#endif
}

inline TVector3 TVector3::operator*( 
	float rhs ) const
{
#if TGON_SUPPORT_SSE
#else
	return TVector3( x*rhs, y*rhs, z*rhs );
#endif
}

inline TVector3 TVector3::operator/( 
	float rhs ) const
{
	assert( rhs != 0.f &&
			"Vector elements can't be divided by zero." );

#if TGON_SUPPORT_SSE
#else
	const float inv = 1.0f / rhs;
	return TVector3( x*inv, y*inv, z*inv );
#endif
}

inline TVector3 TVector3::operator+( ) const
{
	return *this;
}

inline TVector3 TVector3::operator-( ) const
{
#if TGON_SUPPORT_SSE
#else
	return TVector3( -x, -y, -z );
#endif
}

inline TVector3& TVector3::operator+=(
	const TVector3& rhs )
{
#if TGON_SUPPORT_SSE
#else
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
#endif

	return *this;
}

inline TVector3& TVector3::operator-=(
	const TVector3& rhs )
{
#if TGON_SUPPORT_SSE
#else
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
#endif

	return *this;
}

inline TVector3& TVector3::operator*=(
	const TVector3& rhs )
{
#if TGON_SUPPORT_SSE
#else
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
#endif

	return *this;
}

inline TVector3& TVector3::operator*=(
	float rhs )
{
#if TGON_SUPPORT_SSE
#else
	x *= rhs;
	y *= rhs;
	z *= rhs;
#endif

	return *this;
}

inline TVector3& TVector3::operator/=(
	float rhs )
{
#if TGON_SUPPORT_SSE
#else
	const float inv = 1.0f / rhs;

	x *= inv;
	y *= inv;
	z *= inv;
#endif

	return *this;
}

inline bool TVector3::operator==(
	const TVector3& rhs ) const
{
#if TGON_SUPPORT_SSE
	return _mm_cmpeq_ps( reg, rhs.reg );
#else
	return ( x == rhs.x && y == rhs.y && z == rhs.z );
#endif
}

inline bool TVector3::operator!=(
	const TVector3& rhs ) const
{
	return !( this->operator==( rhs ));
}

inline float& TVector3::operator[](
	int32_t index )
{
	assert(( index < 3 && index > -1 ) &&
		"TVector3 index out of range" );

#if TGON_SUPPORT_SSE
#else
	return *( &x + index );
#endif
}

inline float TVector3::operator[](
	int32_t index ) const
{
	assert(( index < 3 && index > -1 ) &&
		"TVector3 index out of range" );

#if TGON_SUPPORT_SSE
#else
	return *( &x + index );
#endif
}

#if TGON_SUPPORT_SSE
inline TVector3::TVector3( __m128 rhs ) :
	reg( rhs )
{
}
#endif

inline float TVector3::Dot(
	const TVector3& a, 
	const TVector3& b ) 
{
#if TGON_SUPPORT_SSE
#else
	return ( a.x * b.x ) +
		   ( a.y * b.y ) +
		   ( a.z * b.z );
#endif
}

inline TVector3 TVector3::Cross(
	const TVector3& a, 
	const TVector3& b )
{
#if TGON_SUPPORT_SSE
#else
	return {( a.y * b.z )-( a.z * b.y ),
			( a.z * b.x )-( a.x * b.z ),
			( a.x * b.y )-( a.y * b.x )};
#endif
}

inline float TVector3::Distance(
	const TVector3& a, 
	const TVector3& b )
{
	return ( a-b ).Length( );
}

inline float TVector3::Length( ) const
{
#if TGON_SUPPORT_SSE
#else
	return std::sqrtf( this->LengthSq( ));
#endif
}

inline float TVector3::LengthSq( ) const
{
#if TGON_SUPPORT_SSE
#else
	return x*x + y*y + z*z;
#endif
}

inline void TVector3::Normalize( )
{
#if TGON_SUPPORT_SSE
#else
	const float inv = 1.f / this->Length( );

	x *= inv;
	y *= inv;
	z *= inv;
#endif
}


}
