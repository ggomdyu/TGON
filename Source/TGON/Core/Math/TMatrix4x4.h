/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../Platform/Config/Build.h"

//#include "../Platform/Slate/PlatformSIMD.h"
//#if TGON_SUPPORT_SSE
//#	include <xmmintrin.h>
//#endif
#undef TGON_SUPPORT_SSE

namespace tgon
{


struct TGON_API TMatrix4x4
{
public:
	static const TMatrix4x4 Identity;

	static const TMatrix4x4 Zero;

	
	/*
		Cons/Destructor
	*/
public:
	TMatrix4x4( );
	
	TMatrix4x4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33 );
	
	TMatrix4x4( const struct TMatrix3x3& );


	/*
		Operators
	*/
public:
	TMatrix4x4 operator+( const TMatrix4x4& ) const;

	TMatrix4x4 operator-( const TMatrix4x4& ) const;

	TMatrix4x4 operator*( const TMatrix4x4& ) const;

	TMatrix4x4 operator*( float ) const;

	const TMatrix4x4& operator+=( const TMatrix4x4& );

	const TMatrix4x4& operator-=( const TMatrix4x4& );

	const TMatrix4x4& operator*=( const TMatrix4x4& );

	bool operator==( const TMatrix4x4& rhs ) const;

	bool operator!=( const TMatrix4x4& rhs ) const;

	float* operator[]( int32_t index );

	const float* operator[]( int32_t index ) const;


	/*
		Commands
	*/
public:
	static TMatrix4x4 Scale( float x, float y, float z );

	static TMatrix4x4 RotateX( float theta );

	static TMatrix4x4 RotateY( float theta );

	static TMatrix4x4 RotateZ( float theta );

	static TMatrix4x4 Translate( float x, float y, float z );

	static TMatrix4x4 View( const struct TVector3& eyePt, const struct TVector3& lookAt, const struct TVector3& up );
	
	static TMatrix4x4 PerspectiveFovLH( float fovY, float aspect, float nearZ, float farZ );

	static TMatrix4x4 Viewport( float x, float y, float width, float height, float minZ, float maxZ );

	void Transpose( );

	void Inverse( );


	/*
		Member variable
	*/
public:
	float _00, _01, _02, _03,
		  _10, _11, _12, _13,
		  _20, _21, _22, _23,
		  _30, _31, _32, _33;
};


#if TGON_SUPPORT_SSE
inline TMatrix4x4::TMatrix4x4( )
{
    _mm_storeu_ps( &_00, _mm_set_ps( 0.0f, 0.0f, 0.0f, 1.0f ));
	_mm_storeu_ps( &_10, _mm_set_ps( 0.0f, 0.0f, 1.0f, 0.0f ));
	_mm_storeu_ps( &_20, _mm_set_ps( 0.0f, 1.0f, 0.0f, 0.0f ));
	_mm_storeu_ps( &_30, _mm_set_ps( 1.0f, 0.0f, 0.0f, 0.0f ));
}
#else
inline TMatrix4x4::TMatrix4x4( ) :
	_00( 1.0f ), _01( 0.0f ), _02( 0.0f ), _03( 0.0f ),
	_10( 0.0f ), _11( 1.0f ), _12( 0.0f ), _13( 0.0f ),
	_20( 0.0f ), _21( 0.0f ), _22( 1.0f ), _23( 0.0f ),
	_30( 0.0f ), _31( 0.0f ), _32( 0.0f ), _33( 1.0f )
{
}
#endif

inline TMatrix4x4 TMatrix4x4::operator+(
	const TMatrix4x4& rhs ) const
{
#if TGON_SUPPORT_SSE
	TMatrix4x4 ret;
	_mm_storeu_ps( &ret._00, _mm_add_ps( _mm_loadu_ps( &_00 ), _mm_loadu_ps( &rhs._00 )));
	_mm_storeu_ps( &ret._10, _mm_add_ps( _mm_loadu_ps( &_10 ), _mm_loadu_ps( &rhs._10 )));
	_mm_storeu_ps( &ret._20, _mm_add_ps( _mm_loadu_ps( &_20 ), _mm_loadu_ps( &rhs._20 )));
	_mm_storeu_ps( &ret._30, _mm_add_ps( _mm_loadu_ps( &_30 ), _mm_loadu_ps( &rhs._30 )));
	
	return ret;
#else
	return TMatrix4x4(
		_00 +rhs._00, _01+rhs._01, _02+rhs._02, _03+rhs._03,
		_10 +rhs._10, _11+rhs._11, _12+rhs._12, _13+rhs._13,
		_20 +rhs._20, _21+rhs._21, _22+rhs._22, _23+rhs._23,
		_30 +rhs._30, _31+rhs._31, _32+rhs._32, _33+rhs._33 );
#endif
}

inline const TMatrix4x4& TMatrix4x4::operator*=(
	const TMatrix4x4& rhs )
{
	*this = ( *this )*rhs;
	return *this;
}

inline bool TMatrix4x4::operator==( const TMatrix4x4& rhs ) const
{
	for ( int i = 0; i < 16; ++i )
	{
		if (( &( _00 ))[i] != ( &( rhs._00 ))[i] )
		{
			return false;
		}
	}
	return true;
}

inline float* TMatrix4x4::operator[](
	int32_t index )
{
	assert(( index < 4 || index > -1 ) && "TMatrix4x4 index out of range" );
	return ( &_00 + index*4 );
}

inline const float* TMatrix4x4::operator[](
	int32_t index ) const
{
	assert(( index < 4 || index > -1 ) && "TMatrix4x4 index out of range" );
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
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return {
		1.f, 0.f,     0.f,    0.f,
		0.f, radCos,  radSin, 0.f,
		0.f, -radSin, radCos, 0.f,
		0.f, 0.f,     0.f,    1.f
	};
}

inline TMatrix4x4 TMatrix4x4::RotateY( float theta )
{
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return {
		radCos, 0.f, -radSin, 0.f,
		0.f,    1.f, 0.f,     0.f,
		radSin, 0.f, radCos,  0.f,
		0.f,    0.f, 0.f,     1.f
	};
}

inline TMatrix4x4 TMatrix4x4::RotateZ( float theta )
{
	const float radCos = cosf( theta );
	const float radSin = sinf( theta );

	return{
		radCos,  radSin, 0.f, 0.f,
		-radSin, radCos, 0.f, 0.f,
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
