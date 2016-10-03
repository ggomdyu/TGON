/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/PlatformInclude.h"


namespace tgon
{


struct TGON_API Vector3
{
	// 
	// Static Variables
	// 
public:
	static const Vector3 Forward;	// 0, 0, 1
	static const Vector3 Back;		// 0, 0, -1
	static const Vector3 Up;		// 0, 1, 0
	static const Vector3 Down;		// 0, -1, 0
	static const Vector3 Left;		// -1, 0, 0
	static const Vector3 Right;		// 1, 0, 0
	static const Vector3 One;		// 0, 0, 0
	static const Vector3 Zero;		// 1, 1, 1

	// 
	// Ctor/Dtor
	// 
public:
	/* @note	Initialize member element as 0 */
    constexpr Vector3( ) noexcept;

	/* @note	Specify initial value of member element */
	constexpr Vector3( float x, float y, float z ) noexcept;

    // 
	// Operators
	// 
public:
	const Vector3 operator+( const Vector3& ) const noexcept;
	const Vector3 operator-( const Vector3& ) const noexcept;
	const Vector3 operator*( const Vector3& ) const noexcept;
	friend const Vector3 operator*( float lhs, const Vector3& rhs ) noexcept;
	const Vector3 operator*( float ) const noexcept;
	const Vector3 operator/( float ) const;
	const Vector3 operator+( ) const noexcept;
	const Vector3 operator-( ) const noexcept;
	Vector3& operator+=( const Vector3& ) noexcept;
	Vector3& operator-=( const Vector3& ) noexcept;
	Vector3& operator*=( const Vector3& ) noexcept;
	Vector3& operator*=( float ) noexcept;
	Vector3& operator/=( float );
	bool operator==( const Vector3& ) const noexcept;
	bool operator!=( const Vector3& ) const noexcept;
	float& operator[]( std::size_t ) noexcept;
	float operator[]( std::size_t ) const noexcept;
	
	// 
	// Commands
	// 
public:
	static float Dot( const Vector3& a, const Vector3& b ) noexcept;
	static Vector3 Cross( const Vector3& a, const Vector3& b ) noexcept;
	static float Angle( const Vector3& a, const Vector3& b ) noexcept;
	static float Distance( const Vector3& a, const Vector3& b ) noexcept;
	float& At( std::size_t index );
	float At( std::size_t index ) const;
	float Length( ) const noexcept;
	float LengthSq( ) const noexcept;
	void Normalize( );
	const Vector3 Normalized( ) const;
	void TransformCoord( const struct Matrix4x4& ) noexcept;
	void TransformNormal( const struct Matrix4x4& ) noexcept;
	
	// 
	// Variables
	// 
public:
	float x, y, z;
};

constexpr Vector3::Vector3( ) noexcept :
	x( 0.f ),
	y( 0.f ),
	z( 0.f )
{
}

constexpr Vector3::Vector3( float x, float y, float z ) noexcept :
	x( x ), 
	y( y ), 
	z( z )
{
}

inline const Vector3 Vector3::operator+( const Vector3& rhs ) const noexcept
{
	return Vector3( x+rhs.x, y+rhs.y, z+rhs.z );
}

inline const Vector3 Vector3::operator-( const Vector3& rhs ) const noexcept
{
	return Vector3( x-rhs.x, y-rhs.y, z-rhs.z );
}

inline const Vector3 Vector3::operator*( const Vector3& rhs ) const noexcept
{
	return Vector3( x*rhs.x, y*rhs.y, z*rhs.z );
}

inline const Vector3 Vector3::operator*( float rhs ) const noexcept
{
	return Vector3( x*rhs, y*rhs, z*rhs );
}

inline const Vector3 operator*( float lhs, const Vector3& rhs ) noexcept
{
	return rhs * lhs;
}

inline const Vector3 Vector3::operator/( float rhs ) const
{
	assert( rhs != 0.f && "Vector elements can't be divided by zero." );

	const float inv = 1.0f / rhs;

	return Vector3( x*inv, y*inv, z*inv );
}

inline const Vector3 Vector3::operator+( ) const noexcept
{
	return *this;
}

inline const Vector3 Vector3::operator-( ) const noexcept
{
	return Vector3( -x, -y, -z );
}

inline Vector3& Vector3::operator+=( const Vector3& rhs ) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline Vector3& Vector3::operator-=( const Vector3& rhs ) noexcept
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=( const Vector3& rhs ) noexcept
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=( float rhs ) noexcept
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

inline Vector3& Vector3::operator/=( float rhs )
{
	const float inv = 1.0f / rhs;

	x *= inv;
	y *= inv;
	z *= inv;

	return *this;
}

inline bool Vector3::operator==( const Vector3& rhs ) const noexcept
{
	return ( x == rhs.x && y == rhs.y && z == rhs.z );
}

inline bool Vector3::operator!=( const Vector3& rhs ) const noexcept
{
	return ( x != rhs.x || y != rhs.y || z != rhs.z );
}

inline float& Vector3::operator[]( std::size_t index ) noexcept
{
	return *( &x + index );
}

inline float Vector3::operator[]( std::size_t index ) const noexcept
{
	return *( &x + index );
}

inline float& Vector3::At( std::size_t index )
{
	assert(( index < 3 && index > -1 ) && "Vector3 index out of range" );
	return *( &x + index );
}

inline float Vector3::At( std::size_t index ) const
{
	assert(( index < 3 && index > -1 ) && "Vector3 index out of range" );
	return *( &x + index );
}

inline float Vector3::Dot( const Vector3& a, const Vector3& b ) noexcept
{
	return ( a.x*b.x ) + ( a.y*b.y ) + ( a.z*b.z );
}

inline Vector3 Vector3::Cross( const Vector3& a, const Vector3& b ) noexcept
{
	return {( a.y*b.z ) - ( a.z*b.y ),
			( a.z*b.x ) - ( a.x*b.z ),
			( a.x*b.y ) - ( a.y*b.x )};
}

inline float Vector3::Distance( const Vector3& a, const Vector3& b ) noexcept
{
	return ( a-b ).Length( );
}

inline float Vector3::Length( ) const noexcept
{
	return std::sqrtf( x*x + y*y + z*z );
}

inline float Vector3::LengthSq( ) const noexcept
{
	return x*x + y*y + z*z;
}

inline void Vector3::Normalize( )
{
	const float inv = 1.f / std::sqrtf( x*x + y*y + z*z );

	x *= inv;
	y *= inv;
	z *= inv;
}

inline const Vector3 Vector3::Normalized( ) const
{
	const float inv = 1.f / std::sqrtf( x*x + y*y + z*z );

	return Vector3( x*inv, y*inv, z*inv );
}


} /*namespace tgon*/