/*
* 작성자 : 차준호
* 작성일 : 2016-03-14
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <iostream>
#include <stdint.h>

#include "../Config/Platform/PlatformSIMD.h"
#include "../Config/Platform/PlatformProperty.h"

namespace tgon
{


struct Vector3D
{
public:
	/*
		Cons/Destructors
	*/
    Vector3D( );
	Vector3D( const float x,
			  const float y,
			  const float z );
#ifdef TGON_SUPPORT_SIMD
	explicit Vector3D( TReg128 );
#endif

	/*
		Utilities
	*/
	static float DotProduct( const Vector3D& first,
							 const Vector3D& second );
	static Vector3D CrossProduct( const Vector3D& first,
								  const Vector3D& second );

	float Length( ) const;
	float LengthSq( ) const;

	void Normalize( );

public:
	/*
		TODO: Why don't you using 'Template expression'?
	*/

    // Arithmetic operators
	Vector3D operator+( const Vector3D& ) const;
	Vector3D operator-( const Vector3D& ) const;
	Vector3D operator*( const Vector3D& ) const;
	Vector3D operator*( const float ) const;
	Vector3D operator/( const float ) const;

	// Unary operators
	Vector3D operator+( ) const;
	Vector3D operator-( ) const;

	// Compound assignment operators
	Vector3D& operator+=( const Vector3D& );
	Vector3D& operator-=( const Vector3D& );
	Vector3D& operator*=( const Vector3D& );
	Vector3D& operator*=( const float );
	Vector3D& operator/=( const float );

	// Comparison operators
	bool operator==( const Vector3D& ) const;
	bool operator!=( const Vector3D& ) const;

	float& operator[]( const int32_t );
	float operator[]( const int32_t ) const;
	
private:
	/* Components */

#ifdef TGON_SUPPORT_SIMD
	TReg128 v;
#else
	float x, y, z;
#endif
};


}

#include "Vector3D.hpp"