#include "PrecompiledHeader.h"
#include "TVector3.h"

#include "TMath.h"
#include "TMatrix4x4.h"


const tgon::TVector3 tgon::TVector3::Forward( 0.f, 0.f, 1.f );
const tgon::TVector3 tgon::TVector3::Back( 0.f, 0.f, -1.f );
const tgon::TVector3 tgon::TVector3::Up( 0.f, 1.f, 0.f );
const tgon::TVector3 tgon::TVector3::Down( 0.f, -1.f, 0.f );
const tgon::TVector3 tgon::TVector3::Left( 1.f, 0.f, 0.f );
const tgon::TVector3 tgon::TVector3::Right( 1.f, 0.f, 0.f );
const tgon::TVector3 tgon::TVector3::One( 0.f, 0.f, 0.f );
const tgon::TVector3 tgon::TVector3::Zero( 0.f, 0.f, 0.f );


void tgon::TVector3::TransformCoord(
	const TMatrix4x4& rhs )
{
	// TVector3's w element is '1'

	const float transX =
		x*rhs._00 + y*rhs._10 + z*rhs._20 + rhs._30;
	const float transY =
		x*rhs._01 + y*rhs._11 + z*rhs._21 + rhs._31;
	const float transZ =
		x*rhs._02 + y*rhs._12 + z*rhs._22 + rhs._32;
	const float transW =
		x*rhs._03 + y*rhs._13 + z*rhs._23 + rhs._33;

	x = transX;
	y = transY;
	z = transZ;

	if ( std::abs( transW-1.0f ) >= EPSILON )
	{		
		const float inv = 1.f / transW;

		x *= inv;
		y *= inv;
		z *= inv;
	}
}

void tgon::TVector3::TransformNormal(
	const TMatrix4x4& rhs )
{
	// TVector3's w element is '0'

	const float transX =
		x*rhs._00 + y*rhs._10 + z*rhs._20;
	const float transY =
		x*rhs._01 + y*rhs._11 + z*rhs._21;
	const float transZ =
		x*rhs._02 + y*rhs._12 + z*rhs._22;
	
	x = transX;
	y = transY;
	z = transZ;
}