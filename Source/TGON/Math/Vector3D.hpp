#pragma once
#include "Vector3D.h"

#include <cassert>

#include "../Config/Platform/PlatformProperty.h"
#include "../Config/Compiler/SyntaxCompatible.hpp"


#ifdef TGON_SUPPORT_SIMD
tgon::Vector3D::Vector3D( ) :
	v( MakeReg128( ))
{

}
#else
tgon::Vector3D::Vector3D( ) :
	x( 0.f ),
	y( 0.f ),
	z( 0.f )
{
}
#endif


#ifdef TGON_SUPPORT_SIMD
tgon::Vector3D::Vector3D(
		const float x, const float y, const float z ) :
	v( MakeReg128( x, y, z ))
{
}
#else
tgon::Vector3D::Vector3D(
		const float x, const float y, const float z ) :
	x( x ), y( y ), z( z )
{
}
#endif

inline tgon::Vector3D tgon::Vector3D::operator+( const Vector3D& rhs ) const
{
#ifdef TGON_SUPPORT_SIMD
	return Vector3D( v + rhs.v );
#else
	return Vector3D( x+rhs.x, y+rhs.y, z+rhs.z );
#endif
}

//inline tgon::Vector3D tgon::Vector3D::operator-(
//	const Vector3D& rhs ) const
//{
//#ifdef TGON_SUPPORT_SIMD
//	return Vector3D( v - rhs.v );
//#else
//	return Vector3D( x-rhs.x,
//					 y-rhs.y,
//					 z-rhs.z );
//#endif
//}
//
//inline Vector3D tgon::Vector3D::operator*(
//	const Vector3D& rhs ) const
//{
//#ifdef TGON_SUPPORT_SIMD
//	return Vector3D( v * rhs.v );
//#else
//	return Vector3D( x*rhs.x,
//					 y*rhs.y,
//					 z*rhs.z );
//#endif
//}
//
//inline Vector3D tgon::Vector3D::operator*(
//	const float rhs ) const
//{
//#ifdef TGON_SUPPORT_SIMD
//	return Vector3D( v * rhs );
//#else
//	return Vector3D( x*rhs,
//					 y*rhs, 
//					 z*rhs );
//#endif
//}
//
//inline Vector3D tgon::Vector3D::operator/(
//	const float rhs ) const
//{
//#ifdef TGON_SUPPORT_SIMD
//	return Vector3D( v / rhs );
//#else
//	const float inv = 1.0f / rhs;
//
//	return Vector3D( x*inv,
//					 y*inv,
//					 z*inv );
//#endif
//}
//
//inline Vector3D& tgon::Vector3D::operator+=(
//	const Vector3D& rhs )
//{
//#ifdef TGON_SUPPORT_SIMD
//	v = v + rhs.v;
//#else
//	x += rhs.x;
//	y += rhs.y;
//	z += rhs.z;
//#endif
//	return *this;
//}
//
//inline Vector3D& tgon::Vector3D::operator-=(
//	const Vector3D& rhs )
//{
//#ifdef TGON_SUPPORT_SIMD
//	v = v - rhs.v;
//#else
//	x -= rhs.x;
//	y -= rhs.y;
//	z -= rhs.z;
//#endif
//	return *this;
//}
//
//inline Vector3D& tgon::Vector3D::operator*=( const Vector3D& rhs )
//{
//#ifdef TGON_SUPPORT_SIMD
//	v = v * rhs.v;
//#else
//	x *= rhs.x;
//	y *= rhs.y;
//	z *= rhs.z;
//#endif
//	return *this;
//}
//
//inline Vector3D& tgon::Vector3D::operator*=( const float rhs )
//{
//#ifdef TGON_SUPPORT_SIMD
//	v = v * rhs;
//#else
//	x *= rhs;
//	y *= rhs;
//	z *= rhs;
//#endif
//	return *this;
//}
//
//inline Vector3D& tgon::Vector3D::operator/=( const float rhs )
//{
//#ifdef TGON_SUPPORT_SIMD
//	v = v / rhs;
//#else
//	const float inv = 1.0f / rhs;
//
//	x *= inv;
//	y *= inv;
//	z *= inv;
//#endif
//
//	return *this;
//}
//
//TGON_FORCEINLINE bool tgon::Vector3D::operator==( const Vector3D& rhs ) const
//{
//#ifdef TGON_SUPPORT_SSE2
//	return ( operator[]( 0 ) == rhs[0] );
//#else
//	return ( x == rhs.x && y == rhs.y && z == rhs.z );
//#endif
//}
//
//inline bool tgon::Vector3D::operator!=( const Vector3D& rhs ) const
//{
//	return !( this->operator==( rhs ));
//}
//
//inline float& tgon::Vector3D::operator[]( const int32_t index )
//{
//	assert( index < 3 &&
//			"Vector3D index out of range" );
//
//#ifdef TGON_SUPPORT_SIMD
//	return v.m128_f32[index];
//#else
//	return ( index == 0 ) ? x :
//		   ( index == 1 ) ? y : 
//		   ( index == 2 ) ? z : z;
//#endif
//}
//
//inline float tgon::Vector3D::operator[]( const int32_t index ) const
//{
//	assert( index < 3 &&
//			"Vector3D index out of range" );
//
//#ifdef TGON_SUPPORT_SIMD
//	return v.m128_f32[index];
//#else
//	return ( &x )+index;
//#endif
//}
//
//inline float tgon::Vector3D::DotProduct(
//	const Vector3D& first,
//	const Vector3D& second ) 
//{
//#ifdef TGON_SUPPORT_SIMD
//	_mm_shuffle_ps( first.v, second.v, _MM_SHUFFLE( 0, 1, 2, 3 ));
//#else
//	return ( first.x*second.x ) +
//		   ( first.y*second.y ) +
//		   ( first.z*second.z );
//#endif
//}
//
//inline Vector3D tgon::Vector3D::CrossProduct(
//		const Vector3D& first,
//		const Vector3D& second )
//{
//	Vector3D ret;
//#ifdef TGON_SUPPORT_SIMD
//
//#else
//
//	ret.x = ( first.y*second.z ) - ( first.z*second.y );
//	ret.y = ( first.z*second.x ) - ( first.x*second.z );
//	ret.z = ( first.x*second.y ) - ( first.y*second.x );
//
//#endif
//	return ret;
//}
//
//
//inline float tgon::Vector3D::Length( ) const 
//{
//#ifdef TGON_SUPPORT_SIMD
//#else
//	return std::sqrt( x*x + y*y + z*z );
//#endif
//	return 0.0f;
//}
//
//
//float tgon::Vector3D::LengthSq( ) const 
//{
//#ifdef TGON_SUPPORT_SIMD
//#else
//	return x*x + y*y + z*z;
//#endif
//}
//
//
//void tgon::Vector3D::Normalize( ) 
//{
//#ifdef TGON_SUPPORT_SIMD
//
//#else
//	const float inv = ( 1.0f / Length( ));
//
//	x *= inv;
//	y *= inv;
//	z *= inv;
//#endif
//}