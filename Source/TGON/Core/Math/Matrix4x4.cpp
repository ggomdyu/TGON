#include "PrecompiledHeader.h"
#include "Matrix4x4.h"

#include "Matrix3x3.h"
#include "Vector3.h"


namespace tgon
{


const Matrix4x4 Matrix4x4::Identity(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f );

const Matrix4x4 Matrix4x4::Zero(
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f );

Matrix4x4::Matrix4x4(
	float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33 
) : 
	_00( _00 ), _01( _01 ), _02( _02 ), _03( _03 ),
	_10( _10 ), _11( _11 ), _12( _12 ), _13( _13 ),
	_20( _20 ), _21( _21 ), _22( _22 ), _23( _23 ),
	_30( _30 ), _31( _31 ), _32( _32 ), _33( _33 )
{
}

Matrix4x4::Matrix4x4( const Matrix3x3& rhs ) :
	_00( rhs._00 ), _01( rhs._01 ), _02( rhs._02 ), _03( 0.f ),
	_10( rhs._10 ), _11( rhs._11 ), _12( rhs._12 ), _13( 0.f ),
	_20( rhs._20 ), _21( rhs._21 ), _22( rhs._22 ), _23( 0.f ),
	_30( 0.f ),		_31( 0.f ),		_32( 0.f ),		_33( 1.f )
{
}

Matrix4x4 Matrix4x4::operator-( const Matrix4x4& rhs ) const
{
	return {
		_00-rhs._00, _01-rhs._01, _02-rhs._02, _03-rhs._03,
		_10-rhs._10, _11-rhs._11, _12-rhs._12, _13-rhs._13,
		_20-rhs._20, _21-rhs._21, _22-rhs._22, _23-rhs._23,
		_30-rhs._30, _31-rhs._31, _32-rhs._32, _33-rhs._33
	};
}

Matrix4x4 Matrix4x4::operator*( const Matrix4x4& rhs ) const
{
	return {
		_00*rhs._00 + _01*rhs._10 + _02*rhs._20 + _03*rhs._30,
		_00*rhs._01 + _01*rhs._11 + _02*rhs._21 + _03*rhs._31,
		_00*rhs._02 + _01*rhs._12 + _02*rhs._22 + _03*rhs._32,
		_00*rhs._03 + _01*rhs._13 + _02*rhs._23 + _03*rhs._33,

		_10*rhs._00 + _11*rhs._10 + _12*rhs._20 + _13*rhs._30,
		_10*rhs._01 + _11*rhs._11 + _12*rhs._21 + _13*rhs._31,
		_10*rhs._02 + _11*rhs._12 + _12*rhs._22 + _13*rhs._32,
		_10*rhs._03 + _11*rhs._13 + _12*rhs._23 + _13*rhs._33,

		_20*rhs._00 + _21*rhs._10 + _22*rhs._20 + _23*rhs._30,
		_20*rhs._01 + _21*rhs._11 + _22*rhs._21 + _23*rhs._31,
		_20*rhs._02 + _21*rhs._12 + _22*rhs._22 + _23*rhs._32,
		_20*rhs._03 + _21*rhs._13 + _22*rhs._23 + _23*rhs._33,

		_30*rhs._00 + _31*rhs._10 + _32*rhs._20 + _33*rhs._30,
		_30*rhs._01 + _31*rhs._11 + _32*rhs._21 + _33*rhs._31,
		_30*rhs._02 + _31*rhs._12 + _32*rhs._22 + _33*rhs._32,
		_30*rhs._03 + _31*rhs._13 + _32*rhs._23 + _33*rhs._33
	};
}

const Matrix4x4& Matrix4x4::operator+=( const Matrix4x4& rhs )
{
	_00 += rhs._00; _01 += rhs._01; _02 += rhs._02; _03 += rhs._03;
	_10 += rhs._10; _11 += rhs._11; _12 += rhs._12; _13 += rhs._13;
	_20 += rhs._20; _21 += rhs._21; _22 += rhs._22; _23 += rhs._23;
	_30 += rhs._30; _31 += rhs._31; _32 += rhs._32; _33 += rhs._33;

	return *this;
}

const Matrix4x4& Matrix4x4::operator-=( const Matrix4x4& rhs )
{
	_00 -= rhs._00; _01 -= rhs._01; _02 -= rhs._02; _03 -= rhs._03;
	_10 -= rhs._10; _11 -= rhs._11; _12 -= rhs._12; _13 -= rhs._13;
	_20 -= rhs._20; _21 -= rhs._21; _22 -= rhs._22; _23 -= rhs._23;
	_30 -= rhs._30; _31 -= rhs._31; _32 -= rhs._32; _33 -= rhs._33;

	return *this;
}

Matrix4x4 Matrix4x4::View(
	const Vector3& eyePt,
	const Vector3& lookAt,
	const Vector3& up )
{
	// Eye ¡æ LookAt = Look direction
	Vector3 l = ( lookAt )-( eyePt );
	l.Normalize( );

	Vector3 r = Vector3::Cross( up, l );
	r.Normalize( );

	Vector3 u = Vector3::Cross( l, r );
	u.Normalize( );

	return {
		r.x, u.x, l.x, 0.f,
		r.y, u.y, l.y, 0.f,
		r.z, u.z, l.z, 0.f,
		-Vector3::Dot( r, eyePt ), -Vector3::Dot( u, eyePt ), -Vector3::Dot( l, eyePt ), 1.f
	};
}

Matrix4x4 Matrix4x4::PerspectiveFovLH(
	float fovY,
	float aspect,
	float nearZ, float farZ )
{
	const float scaleY = 1.f / std::tan( fovY*0.5f );
	const float scaleX = scaleY / aspect;

	return Matrix4x4(
		scaleX, 0.f, 0.f,0.f,
		0.f, scaleY, 0.f, 0.f,
		0.f, 0.f, farZ/( farZ-nearZ ), 1.f,
		0.f, 0.f, ( -farZ*nearZ )/( farZ-nearZ ), 0.f
	);
}

Matrix4x4 Matrix4x4::Viewport( 
	float x, float y, 
	float width, float height,
	float minZ, float maxZ )
{
	const float halfWidth = width*0.5f;
	const float halfHeight = height*0.5f;

	return Matrix4x4(
		halfWidth, 0.f, 0.f, 0.f,
		0.f, -halfHeight, 0.f, 0.f,
		0.f, 0.f, maxZ-minZ, 0.f,
		x+( halfWidth ), y+( halfHeight ), minZ, 1.f
	);
}

Matrix4x4 Matrix4x4::Transpose( const Matrix4x4& rhs )
{
	return {
		rhs._00, rhs._10, rhs._20, rhs._30,
		rhs._01, rhs._11, rhs._21, rhs._31,
		rhs._02, rhs._12, rhs._22, rhs._32,
		rhs._03, rhs._13, rhs._23, rhs._33
	};
}


} /*namespace tgon*/