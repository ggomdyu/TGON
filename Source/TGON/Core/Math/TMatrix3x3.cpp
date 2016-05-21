#include "PrecompiledHeader.h"
#include "TMatrix3x3.h"


const tgon::TMatrix3x3 tgon::TMatrix3x3::Identity(
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f );

const tgon::TMatrix3x3 tgon::TMatrix3x3::Zero(
	0.f, 0.f, 0.f,
	0.f, 0.f, 0.f,
	0.f, 0.f, 0.f );

tgon::TMatrix3x3::TMatrix3x3( ) :
	_00( 1.f ), _01( 0.f ), _02( 0.f ),
	_10( 0.f ), _11( 1.f ), _12( 0.f ),
	_20( 0.f ), _21( 0.f ), _22( 1.f )
{
}

tgon::TMatrix3x3::TMatrix3x3(
	float _00, float _01, float _02,
	float _10, float _11, float _12,
	float _20, float _21, float _22 ) :

	_00( _00 ), _01( _01 ), _02( _02 ),
	_10( _10 ), _11( _11 ), _12( _12 ),
	_20( _20 ), _21( _21 ), _22( _22 )
{
}

tgon::TMatrix3x3 tgon::TMatrix3x3::operator+(
	const TMatrix3x3& rhs ) const
{
	return TMatrix3x3(
		_00+rhs._00, _01+rhs._01, _02+rhs._02,
		_10+rhs._10, _11+rhs._11, _12+rhs._12,
		_20+rhs._20, _21+rhs._21, _22+rhs._22 
	);
}

tgon::TMatrix3x3 tgon::TMatrix3x3::operator-(
	const TMatrix3x3& rhs ) const
{
	return TMatrix3x3(
		_00-rhs._00, _01-rhs._01, _02-rhs._02,
		_10-rhs._10, _11-rhs._11, _12-rhs._12,
		_20-rhs._20, _21-rhs._21, _22-rhs._22
	);
}

tgon::TMatrix3x3 tgon::TMatrix3x3::operator*(
	const TMatrix3x3& rhs ) const
{
	return TMatrix3x3(
		_00*rhs._00 + _01*rhs._10 + _02*rhs._20,
		_00*rhs._01 + _01*rhs._11 + _02*rhs._21,
		_00*rhs._02 + _01*rhs._12 + _02*rhs._22,

		_10*rhs._00 + _11*rhs._10 + _12*rhs._20,
		_10*rhs._01 + _11*rhs._11 + _12*rhs._21,
		_10*rhs._02 + _11*rhs._12 + _12*rhs._22,

		_20*rhs._00 + _21*rhs._10 + _22*rhs._20,
		_20*rhs._01 + _21*rhs._11 + _22*rhs._21,
		_20*rhs._02 + _21*rhs._12 + _22*rhs._22
	);
}

const tgon::TMatrix3x3& tgon::TMatrix3x3::operator+=(
	const TMatrix3x3& rhs )
{
	_00 += rhs._00; _01 += rhs._01; _02 += rhs._02;
	_10 += rhs._10; _11 += rhs._11; _12 += rhs._12;
	_20 += rhs._20; _21 += rhs._21; _22 += rhs._22;

	return *this;
}

const tgon::TMatrix3x3& tgon::TMatrix3x3::operator-=(
	const TMatrix3x3& rhs )
{
	_00 -= rhs._00; _01 -= rhs._01; _02 -= rhs._02;
	_10 -= rhs._10; _11 -= rhs._11; _12 -= rhs._12;
	_20 -= rhs._20; _21 -= rhs._21; _22 -= rhs._22;

	return *this;
}

void tgon::TMatrix3x3::Transpose( )
{
	TMatrix3x3 mat(
		_00, _10, _20,
		_01, _11, _21,
		_02, _12, _22
	);

	*this = mat;
}
