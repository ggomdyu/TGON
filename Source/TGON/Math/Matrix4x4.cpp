#include "PrecompiledHeader.h"
#include "Matrix4x4.h"


Matrix4x4 Matrix4x4::operator+( const Matrix4x4& rhs )
{
	return Matrix4x4(
		m00+rhs.m00,
		m01+rhs.m01,
		m02+rhs.m02,
		m03+rhs.m03,
			   
		m10+rhs.m10,
		m11+rhs.m11,
		m12+rhs.m12,
		m13+rhs.m13,
			   
		m20+rhs.m20,
		m21+rhs.m21,
		m22+rhs.m22,
		m23+rhs.m23,
			   
		m30+rhs.m30,
		m31+rhs.m31,
		m32+rhs.m32,
		m33+rhs.m33 );
}

Matrix4x4 Matrix4x4::operator-( const Matrix4x4& rhs )
{
	return Matrix4x4(
		m00-rhs.m00,
		m01-rhs.m01,
		m02-rhs.m02,
		m03-rhs.m03,
		
		m10-rhs.m10,
		m11-rhs.m11,
		m12-rhs.m12,
		m13-rhs.m13,
		
		m20-rhs.m20,
		m21-rhs.m21,
		m22-rhs.m22,
		m23-rhs.m23,
		
		m30-rhs.m30,
		m31-rhs.m31,
		m32-rhs.m32,
		m33-rhs.m33 );
}

Matrix4x4 Matrix4x4::operator*( const Matrix4x4& rhs )
{
	return Matrix4x4(
		m00*rhs.m00 + m01*rhs.m10 + m02*rhs.m20 + m03*rhs.m30,
		m00*rhs.m01 + m01*rhs.m11 + m02*rhs.m21 + m03*rhs.m31,
		m00*rhs.m02 + m01*rhs.m12 + m02*rhs.m22 + m03*rhs.m32,
		m00*rhs.m03 + m01*rhs.m13 + m02*rhs.m23 + m03*rhs.m33,
		m10*rhs.m00 + m11*rhs.m10 + m12*rhs.m20 + m13*rhs.m30,
		m10*rhs.m01 + m11*rhs.m11 + m12*rhs.m21 + m13*rhs.m31,
		m10*rhs.m02 + m11*rhs.m12 + m12*rhs.m22 + m13*rhs.m32,
		m10*rhs.m03 + m11*rhs.m13 + m12*rhs.m23 + m13*rhs.m33,
		m20*rhs.m00 + m21*rhs.m10 + m22*rhs.m20 + m23*rhs.m30,
		m20*rhs.m01 + m21*rhs.m11 + m22*rhs.m21 + m23*rhs.m31,
		m20*rhs.m02 + m21*rhs.m12 + m22*rhs.m22 + m23*rhs.m32,
		m20*rhs.m03 + m21*rhs.m13 + m22*rhs.m23 + m23*rhs.m33,
		m30*rhs.m00 + m31*rhs.m10 + m32*rhs.m20 + m33*rhs.m30,
		m30*rhs.m01 + m31*rhs.m11 + m32*rhs.m21 + m33*rhs.m31,
		m30*rhs.m02 + m31*rhs.m12 + m32*rhs.m22 + m33*rhs.m32,
		m30*rhs.m03 + m31*rhs.m13 + m32*rhs.m23 + m33*rhs.m33
	);
}

const Matrix4x4& Matrix4x4::operator+=( const Matrix4x4& rhs )
{
	m00 += rhs.m00;
	m01 += rhs.m01;
	m02 += rhs.m02;
	m03 += rhs.m03;

	m10 += rhs.m10;
	m11 += rhs.m11;
	m12 += rhs.m12;
	m13 += rhs.m13;

	m20 += rhs.m20;
	m21 += rhs.m21;
	m22 += rhs.m22;
	m23 += rhs.m23;

	m30 += rhs.m30;
	m31 += rhs.m31;
	m32 += rhs.m32;
	m33 += rhs.m33;

	return *this;
}

const Matrix4x4& Matrix4x4::operator-=( const Matrix4x4& rhs )
{
	m00 -= rhs.m00;
	m01 -= rhs.m01;
	m02 -= rhs.m02;
	m03 -= rhs.m03;
	
	m10 -= rhs.m10;
	m11 -= rhs.m11;
	m12 -= rhs.m12;
	m13 -= rhs.m13;
	
	m20 -= rhs.m20;
	m21 -= rhs.m21;
	m22 -= rhs.m22;
	m23 -= rhs.m23;
	
	m30 -= rhs.m30;
	m31 -= rhs.m31;
	m32 -= rhs.m32;
	m33 -= rhs.m33;

	return *this;
}

const Matrix4x4& Matrix4x4::operator*=( const Matrix4x4& rhs )
{
	return *this;
}