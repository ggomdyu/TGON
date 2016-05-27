/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../Platform/Config/Build.h"


namespace tgon
{


struct TGON_API TMatrix4x4
{
public:
	static const TMatrix4x4 Identity;
	static const TMatrix4x4 Zero;

public:
	static TMatrix4x4 Scale( 
		float x, 
		float y, 
		float z );
	static TMatrix4x4 RotateX( float theta );
	static TMatrix4x4 RotateY( float theta );
	static TMatrix4x4 RotateZ( float theta );
	static TMatrix4x4 Translate( 
		float x, 
		float y, 
		float z );
	
	static TMatrix4x4 View(
		const struct TVector3& eyePt,	 // X axis
		const struct TVector3& lookAt,	 // Y axis
		const struct TVector3& up );	 // Z axis

	static TMatrix4x4 PerspectiveFovLH(
		float fovY,
		float aspect,
		float nearZ, 
		float farZ );

	static TMatrix4x4 Viewport(
		float x, 
		float y,
		float width, 
		float height,
		float minZ, 
		float maxZ );

	void Transpose( );
	void Inverse( );

public:
	TMatrix4x4( );
	TMatrix4x4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33 
	);
	TMatrix4x4( const struct TMatrix3x3& );

	// Arithmetic operators
	TMatrix4x4 operator+( const TMatrix4x4& ) const;
	TMatrix4x4 operator-( const TMatrix4x4& ) const;
	TMatrix4x4 operator*( const TMatrix4x4& ) const;
	TMatrix4x4 operator*( float ) const;

	// Unary operators
	TMatrix4x4 operator+( ) const;
	TMatrix4x4 operator-( ) const;

	// Compound assignment operators
	const TMatrix4x4& operator+=( const TMatrix4x4& );
	const TMatrix4x4& operator-=( const TMatrix4x4& );
	const TMatrix4x4& operator*=( const TMatrix4x4& );

	// Comparison operators
	bool operator==( const TMatrix4x4& rhs ) const;
	bool operator!=( const TMatrix4x4& rhs ) const;

	float* operator[]( int32_t index );
	const float* operator[]( int32_t index ) const;

public:
	float _00, _01, _02, _03,
		  _10, _11, _12, _13,
		  _20, _21, _22, _23,
		  _30, _31, _32, _33;
};

inline const TMatrix4x4& TMatrix4x4::operator*=(
	const TMatrix4x4& rhs )
{
	*this = ( *this )*rhs;
	return *this;
}

inline bool TMatrix4x4::operator==( const TMatrix4x4& rhs ) const
{
	const float* lBegin = &( _00 );
	const float* rBegin = &( rhs._00 );

	for ( int i = 0; i < 16; ++i )
	{
		if ( lBegin[i] == rBegin[i] )
		{
			return false;
		}
	}

	return true;
}

inline float* TMatrix4x4::operator[](
	int32_t index )
{
	assert(( index < 4 || index > -1 ) && 
			"TMatrix4x4 index out of range" );

	return ( &_00 + index*4 );
}

inline const float* TMatrix4x4::operator[](
	int32_t index ) const
{
	assert(( index < 4 || index > -1 ) && 
			"TMatrix4x4 index out of range" );

	return ( &_00 + index*4 );
}

inline TMatrix4x4 TMatrix4x4::Translate(
	float x, float y, float z )
{
	return {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x,	 y,	  z,   1.f
	};
}

inline TMatrix4x4 TMatrix4x4::RotateX( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return {
		1.f, 0.f,     0.f,    0.f,
		0.f, cosRad,  sinRad, 0.f,
		0.f, -sinRad, cosRad, 0.f,
		0.f, 0.f,     0.f,    1.f
	};
}

inline TMatrix4x4 TMatrix4x4::RotateY( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return {
		cosRad, 0.f, -sinRad, 0.f,
		0.f,    1.f, 0.f,     0.f,
		sinRad, 0.f, cosRad,  0.f,
		0.f,    0.f, 0.f,     1.f
	};
}

inline TMatrix4x4 TMatrix4x4::RotateZ( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return{
		cosRad,  sinRad, 0.f, 0.f,
		-sinRad, cosRad, 0.f, 0.f,
		0.f,     0.f,    1.f, 0.f,
		0.f,     0.f,    0.f, 1.f
	};
}

inline TMatrix4x4 TMatrix4x4::Scale(
	float x, 
	float y, 
	float z )
{
	return {
		x,   0.f, 0.f, 0.f,
		0.f, y,	  0.f, 0.f,
		0.f, 0.f, z,   0.f,
		0.f, 0.f, 0.f, 1.f
	};
}


}
