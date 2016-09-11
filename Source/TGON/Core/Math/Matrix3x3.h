/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../Platform/OSAL/PlatformInclude.h"


namespace tgon
{


struct TGON_API Matrix3x3
{
public:
	static const Matrix3x3 Identity;
	static const Matrix3x3 Zero;

public:
	Matrix3x3( );
	Matrix3x3( float _00, float _01, float _02, 
			   float _10, float _11, float _12, 
			   float _20, float _21, float _22 );
	
	Matrix3x3 operator+( const Matrix3x3& ) const;
	Matrix3x3 operator-( const Matrix3x3& ) const;
	Matrix3x3 operator*( const Matrix3x3& ) const;
	Matrix3x3 operator*( float ) const;
	Matrix3x3 operator+( ) const;
	Matrix3x3 operator-( ) const;
	const Matrix3x3& operator+=( const Matrix3x3& );
	const Matrix3x3& operator-=( const Matrix3x3& );
	const Matrix3x3& operator*=( const Matrix3x3& );
	bool operator==( const Matrix3x3& ) const;
	bool operator!=( const Matrix3x3& ) const;
	float* operator[]( int32_t row );
	const float* operator[]( int32_t row ) const;
	
public:
	static Matrix3x3 Scale( float x, float y, float z );
	static Matrix3x3 RotateX( float theta );
	static Matrix3x3 RotateY( float theta );
	static Matrix3x3 RotateZ( float theta );

	void Transpose( );
	void Inverse( );

public:
	float _00, _01, _02,
		  _10, _11, _12,
		  _20, _21, _22;
};

inline const Matrix3x3& Matrix3x3::operator*=(
	const Matrix3x3& rhs )
{
	*this = ( *this )*rhs;
	return *this;
}

inline float* Matrix3x3::operator[](
	int32_t row )
{
	assert(( row < 3 && row > -1 ) && "TMatrix3x3 index out of range" );

	return ( &_00 + row*3 );
}

inline const float* Matrix3x3::operator[](
	int32_t row ) const
{
	assert(( row < 3 && row > -1 ) && "TMatrix3x3 index out of range" );

	return ( &_00 + row*3 );
}

inline Matrix3x3 Matrix3x3::RotateX( float theta )
{
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return {
		1.f, 0.f,     0.f,   
		0.f, radCos,  radSin,
		0.f, -radSin, radCos,
	};
}

inline Matrix3x3 Matrix3x3::RotateY( float theta )
{
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return {
		radCos, 0.f, -radSin,
		0.f,    1.f, 0.f,    
		radSin, 0.f, radCos, 
	};
}

inline Matrix3x3 Matrix3x3::RotateZ( float theta )
{
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return{
		radCos,  radSin, 0.f,
		-radSin, radCos, 0.f,
		0.f,     0.f,    1.f,
	};
}

inline Matrix3x3 Matrix3x3::Scale(
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


} /*namespace tgon*/