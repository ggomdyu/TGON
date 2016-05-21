/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../Platform/Config/BuildOption.h"


namespace tgon
{


struct TGON_API TMatrix3x3
{
public:
	static const TMatrix3x3 Identity;
	static const TMatrix3x3 Zero;

public:
	TMatrix3x3( );
	TMatrix3x3(
		float _00, float _01, float _02, 
		float _10, float _11, float _12, 
		float _20, float _21, float _22 );
	
	// Arithmetic operators
	TMatrix3x3 operator+( const TMatrix3x3& ) const;
	TMatrix3x3 operator-( const TMatrix3x3& ) const;
	TMatrix3x3 operator*( const TMatrix3x3& ) const;
	TMatrix3x3 operator*( float ) const;

	// Unary operators
	TMatrix3x3 operator+( ) const;
	TMatrix3x3 operator-( ) const;

	// Compound assignment operators
	const TMatrix3x3& operator+=( const TMatrix3x3& );
	const TMatrix3x3& operator-=( const TMatrix3x3& );
	const TMatrix3x3& operator*=( const TMatrix3x3& );

	// Comparison operators
	bool operator==( const TMatrix3x3& ) const;
	bool operator!=( const TMatrix3x3& ) const;
	
	float* operator[]( int32_t row );
	const float* operator[]( int32_t row ) const;
	
public:
	static TMatrix3x3 Scale( 
		float x, 
		float y, 
		float z );
	static TMatrix3x3 RotateX( float theta );
	static TMatrix3x3 RotateY( float theta );
	static TMatrix3x3 RotateZ( float theta );

	void Transpose( );
	void Inverse( );

public:
	float _00, _01, _02,
		  _10, _11, _12,
		  _20, _21, _22;
};

inline const TMatrix3x3& TMatrix3x3::operator*=(
	const TMatrix3x3& rhs )
{
	*this = ( *this )*rhs;
	return *this;
}

inline float* TMatrix3x3::operator[](
	int32_t row )
{
	assert(( row < 3 || row > -1 ) && 
			"TMatrix3x3 index out of range" );

	return ( &_00 + row*3 );
}

inline const float* TMatrix3x3::operator[](
	int32_t row ) const
{
	assert(( row < 3 || row > -1 ) && 
			"TMatrix3x3 index out of range" );

	return ( &_00 + row*3 );
}

inline TMatrix3x3 TMatrix3x3::RotateX( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return {
		1.f, 0.f,     0.f,   
		0.f, cosRad,  sinRad,
		0.f, -sinRad, cosRad,
	};
}

inline TMatrix3x3 TMatrix3x3::RotateY( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return {
		cosRad, 0.f, -sinRad,
		0.f,    1.f, 0.f,    
		sinRad, 0.f, cosRad, 
	};
}

inline TMatrix3x3 TMatrix3x3::RotateZ( float theta )
{
	const float cosRad = cosf( theta );
	const float sinRad = sinf( theta );

	return{
		cosRad,  sinRad, 0.f,
		-sinRad, cosRad, 0.f,
		0.f,     0.f,    1.f,
	};
}

inline TMatrix3x3 TMatrix3x3::Scale(
	float x, 
	float y, 
	float z )
{
	return {
		x,   0.f, 0.f,
		0.f, y,	  0.f,
		0.f, 0.f, z,
	};
}


}
