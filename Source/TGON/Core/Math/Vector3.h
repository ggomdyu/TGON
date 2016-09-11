/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/OSAL/PlatformInclude.h"


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
    constexpr Vector3( );

	/* @note	Specify initial value of member element */
	constexpr Vector3( float x, float y, float z );

    // 
	// Operators
	// 
public:
	Vector3 operator+( const Vector3& ) const;
	Vector3 operator-( const Vector3& ) const;
	Vector3 operator*( const Vector3& ) const;
	friend Vector3 operator*( float lhs, const Vector3& rhs );
	Vector3 operator*( float ) const;
	Vector3 operator/( float ) const;
	Vector3 operator+( ) const;
	Vector3 operator-( ) const;
	Vector3& operator+=( const Vector3& );
	Vector3& operator-=( const Vector3& );
	Vector3& operator*=( const Vector3& );
	Vector3& operator*=( float );
	Vector3& operator/=( float );
	bool operator==( const Vector3& ) const;
	bool operator!=( const Vector3& ) const;
	float& operator[]( int32_t );
	float operator[]( int32_t ) const;

	// 
	// Commands
	// 
public:
	static float Dot( const Vector3& a, const Vector3& b );
	static Vector3 Cross( const Vector3& a, const Vector3& b );
	float Length( ) const;
	float LengthSq( ) const;
	static float Angle( const Vector3& a, const Vector3& b );
	static float Distance( const Vector3& a, const Vector3& b );
	void Normalize( );
	void TransformCoord( const struct Matrix4x4& );
	void TransformNormal( const struct Matrix4x4& );

	// 
	// Variables
	// 
public:
	float x, y, z;
};


constexpr Vector3::Vector3( ) :
	x( 0.f ),
	y( 0.f ),
	z( 0.f )
{
}

constexpr Vector3::Vector3( float x, float y, float z ) :
	x( x ), 
	y( y ), 
	z( z )
{
}

inline Vector3 Vector3::operator+( 
	const Vector3& rhs ) const
{
	return Vector3( x+rhs.x, y+rhs.y, z+rhs.z );
}

inline Vector3 Vector3::operator-( const Vector3& rhs ) const
{
	return Vector3( x-rhs.x, y-rhs.y, z-rhs.z );
}

inline Vector3 Vector3::operator*( const Vector3& rhs ) const
{
	return Vector3( x*rhs.x, y*rhs.y, z*rhs.z );
}

inline Vector3 Vector3::operator*( float rhs ) const
{
	return Vector3( x*rhs, y*rhs, z*rhs );
}

inline Vector3 operator*( float lhs, const Vector3& rhs )
{
	return rhs*lhs;
}

inline Vector3 Vector3::operator/( float rhs ) const
{
	assert( rhs != 0.f && "Vector elements can't be divided by zero." );

	const float inv = 1.0f / rhs;
	return Vector3( x*inv, y*inv, z*inv );
}

inline Vector3 Vector3::operator+( ) const
{
	return *this;
}

inline Vector3 Vector3::operator-( ) const
{
	return Vector3( -x, -y, -z );
}

inline Vector3& Vector3::operator+=( const Vector3& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline Vector3& Vector3::operator-=( const Vector3& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=( const Vector3& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

inline Vector3& Vector3::operator*=( float rhs )
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

inline bool Vector3::operator==( const Vector3& rhs ) const
{
	return ( x == rhs.x && y == rhs.y && z == rhs.z );
}

inline bool Vector3::operator!=( const Vector3& rhs ) const
{
	return !( this->operator==( rhs ));
}

inline float& Vector3::operator[]( int32_t index )
{
	assert(( index < 3 && index > -1 ) && "Vector3 index out of range" );
	return *( &x + index );
}

inline float Vector3::operator[]( int32_t index ) const
{
	assert(( index < 3 && index > -1 ) && "Vector3 index out of range" );
	return *( &x + index );
}

inline float Vector3::Dot( const Vector3& a, const Vector3& b ) 
{
	return ( a.x * b.x ) + ( a.y * b.y ) + ( a.z * b.z );
}

inline Vector3 Vector3::Cross( const Vector3& a, const Vector3& b )
{
	return {( a.y * b.z )-( a.z * b.y ),
			( a.z * b.x )-( a.x * b.z ),
			( a.x * b.y )-( a.y * b.x )};
}

inline float Vector3::Distance( const Vector3& a, const Vector3& b )
{
	return ( a-b ).Length( );
}

inline float Vector3::Length( ) const
{
	return std::sqrtf( x*x + y*y + z*z );
}

inline float Vector3::LengthSq( ) const
{
	return x*x + y*y + z*z;
}

inline void Vector3::Normalize( )
{
	const float inv = 1.f / this->Length( );

	x *= inv;
	y *= inv;
	z *= inv;
}


} /*namespace tgon*/