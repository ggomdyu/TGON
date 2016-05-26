/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"
#include "../Core/Math/TVector3.h"


namespace tgon
{


struct TGON_API TQuaternion
{
public:
	static const TQuaternion Zero;
	static const TQuaternion Identity;

public:
	TQuaternion( );

	// In Quaternion, x, y, z means a Axis. w is angle scalar.
	TQuaternion( float x, float y, float z, float w );

	// Pass axis as TVector3. w is angle scalar.
	TQuaternion( const TVector3& v, float w );

	TQuaternion( const TQuaternion& );


public:
    // Arithmetic operators
	TQuaternion operator*( const TQuaternion& ) const;

	// Unary operators
	TQuaternion operator+( ) const;
	TQuaternion operator-( ) const;

	// Compound assignment operators
	TQuaternion& operator*=( const TQuaternion& );

	// Comparison operators
	bool operator==( const TQuaternion& ) const;
	bool operator!=( const TQuaternion& ) const;

	float& operator[]( int32_t );
	float operator[]( int32_t ) const;
	
public:
	struct TMatrix4x4 RotateMatrix( ) const;

public:
	float x, y, z, w;
};


inline TQuaternion::TQuaternion( ) :
	x( 0.f ),
	y( 0.f ),
	z( 0.f ),
	w( 0.f )
{
}

inline TQuaternion::TQuaternion(
	float x, 
	float y, 
	float z,
	float w ) :
	x( x ), 
	y( y ), 
	z( z ),
	w( w )
{
}

inline TQuaternion::TQuaternion( 
	const TQuaternion& rhs ) :
	x( rhs.x ),
	y( rhs.y ),
	z( rhs.z ),
	w( rhs.w )
{
}

inline TQuaternion TQuaternion::operator*(
	const TQuaternion& rhs ) const
{
	return TQuaternion( x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w );
}

inline TQuaternion TQuaternion::operator+( ) const
{
	return *this;
}

inline TQuaternion TQuaternion::operator-( ) const
{
	return TQuaternion( -x, -y, -z, -w );
}

inline TQuaternion& TQuaternion::operator*=(
	const TQuaternion& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;

	return *this;
}

inline bool TQuaternion::operator==(
	const TQuaternion& rhs ) const
{
	return ( x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w );
}

inline bool TQuaternion::operator!=(
	const TQuaternion& rhs ) const
{
	return !( this->operator==( rhs ));
}

inline float& TQuaternion::operator[](
	int32_t index )
{
	assert(( index < 4 && index > -1 ) &&
		"TVector3 index out of range" );

	return *( &x + index );
}

inline float TQuaternion::operator[](
	int32_t index ) const
{
	assert(( index < 4 && index > -1 ) &&
		"TVector3 index out of range" );

	return *( &x + index );
}


}