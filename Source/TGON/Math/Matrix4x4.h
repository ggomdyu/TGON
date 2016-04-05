#pragma once
#include <iostream> 


//#define TGON_FAST_MATRIX 

class Matrix4x4 //: public RefCounter
{
public:
	/*
		Cons/Destructors
	*/
	Matrix4x4( );
	Matrix4x4( float _m00, float _m01, float _m02, float _m03,
			   float _m10, float _m11, float _m12, float _m13,
			   float _m20, float _m21, float _m22, float _m23,
			   float _m30, float _m31, float _m32, float _m33 );

	/*
		Utilities
	*/
	static Matrix4x4 Transpose( _In_ const Matrix4x4& );

	void Rotate( );
	void Inverse( );
	

public:
	// Arithmetic operators
	Matrix4x4 operator+( const Matrix4x4& ) const;
	Matrix4x4 operator-( const Matrix4x4& ) const;
	Matrix4x4 operator*( const Matrix4x4& ) const;
	Matrix4x4 operator*( const float ) const;

	// Unary operators
	Matrix4x4 operator+( ) const;
	Matrix4x4 operator-( ) const;

	// Compound assignment operators
	const Matrix4x4& operator+=( const Matrix4x4& );
	const Matrix4x4& operator-=( const Matrix4x4& );
	const Matrix4x4& operator*=( const Matrix4x4& );

	// Comparison operators
	bool operator==( const Matrix4x4& rhs );
	bool operator!=( const Matrix4x4& rhs );

	Matrix4x4 operator+( const Matrix4x4& );
	Matrix4x4 operator-( const Matrix4x4& );
	Matrix4x4 operator*( const Matrix4x4& );

public:
	float m00, m01, m02, m03,
		  m10, m11, m12, m13,
		  m20, m21, m22, m23,
		  m30, m31, m32, m33;
};


#include "Matrix4x4.hpp"