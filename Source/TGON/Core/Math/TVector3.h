/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"


namespace tgon
{


struct TGON_API TVector3
{
public:
	static const TVector3 Forward;
	static const TVector3 Back;
	static const TVector3 Up;
	static const TVector3 Down;
	static const TVector3 Left;
	static const TVector3 Right;
	static const TVector3 One;
	static const TVector3 Zero;

public:
    TVector3( );
	TVector3( float x, float y, float z );

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
	float x, y, z;
};


inline TVector3::TVector3( ) :
	x( 0.f ),
	y( 0.f ),
	z( 0.f )
{
}

inline TVector3::TVector3( 
	float x, 
	float y, 
	float z ) :
	x( x ), 
	y( y ), 
	z( z )
{
}

inline TVector3 TVector3::operator+( 
	const TVector3& rhs ) const
{
	return TVector3( x+rhs.x, y+rhs.y, z+rhs.z );
}

inline TVector3 TVector3::operator-( 
	const TVector3& rhs ) const
{
	return TVector3( x-rhs.x, y-rhs.y, z-rhs.z );
}

inline TVector3 TVector3::operator*(
	const TVector3& rhs ) const
{
	return TVector3( x*rhs.x, y*rhs.y, z*rhs.z );
}

inline TVector3 TVector3::operator*( 
	float rhs ) const
{
	return TVector3( x*rhs, y*rhs, z*rhs );
}

inline TVector3 TVector3::operator/( 
	float rhs ) const
{
	assert( rhs != 0.f &&
			"Vector elements can't be divided by zero." );

	const float inv = 1.0f / rhs;
	return TVector3( x*inv, y*inv, z*inv );
}

inline TVector3 TVector3::operator+( ) const
{
	return TVector3( std::abs(x), std::abs(y), std::abs(z));
}

inline TVector3& TVector3::operator+=(
	const TVector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline TVector3& TVector3::operator-=(
	const TVector3& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline TVector3& TVector3::operator*=(
	const TVector3& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

inline TVector3& TVector3::operator*=(
	float rhs )
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

inline TVector3& TVector3::operator/=(
	float rhs )
{
	const float inv = 1.0f / rhs;

	x *= inv;
	y *= inv;
	z *= inv;

	return *this;
}

inline bool TVector3::operator==(
	const TVector3& rhs ) const
{
	return ( x == rhs.x &&
			 y == rhs.y &&
			 z == rhs.z );
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

	return *( &x + index );
}

inline float TVector3::operator[](
	int32_t index ) const
{
	assert(( index < 3 && index > -1 ) &&
		"TVector3 index out of range" );

	return *( &x + index );
}

inline float TVector3::Dot(
	const TVector3& a, const TVector3& b ) 
{
	return ( a.x * b.x ) +
		   ( a.y * b.y ) +
		   ( a.z * b.z );
}

inline TVector3 TVector3::Cross(
	const TVector3& a,  const TVector3& b )
{
	return {( a.y * b.z )-( a.z * b.y ),
			( a.z * b.x )-( a.x * b.z ),
			( a.x * b.y )-( a.y * b.x )};
}

//inline float TVector3::Angle(
//	const TVector3& a, const TVector3& b )
//{
//	return std::acosf(
//		Dot( a, b ) / ( a.Length( )*b.Length( )));
//}

inline float TVector3::Distance(
	const TVector3& a, const TVector3& b )
{
	return ( a-b ).Length( );
}

inline float TVector3::Length( ) const
{
	return std::sqrtf( this->LengthSq( ));
}

inline float TVector3::LengthSq( ) const
{
	return x*x + y*y + z*z;
}

inline void TVector3::Normalize( )
{
	const float inv = 1.f / this->Length( );

	x *= inv;
	y *= inv;
	z *= inv;
}


}