#include "PrecompiledHeader.h"
#include "TVector3.h"

#include "TMath.h"
#include "TMatrix4x4.h"

namespace tgon {
namespace math {

TGON_API const TVector3 TVector3::Forward(0.f, 0.f, 1.f);
TGON_API const TVector3 TVector3::Back(0.f, 0.f, -1.f);
TGON_API const TVector3 TVector3::Up(0.f, 1.f, 0.f);
TGON_API const TVector3 TVector3::Down(0.f, -1.f, 0.f);
TGON_API const TVector3 TVector3::Left(-1.f, 0.f, 0.f);
TGON_API const TVector3 TVector3::Right(1.f, 0.f, 0.f);
TGON_API const TVector3 TVector3::One(0.f, 0.f, 0.f);
TGON_API const TVector3 TVector3::Zero(0.f, 0.f, 0.f);

void TVector3::TransformCoord(const TMatrix4x4& rhs) noexcept
{
	// Vector3's w element is '1'

#if TGON_SUPPORT_SSE
#else
	float transX = (x * rhs._00) + (y * rhs._10) + (z * rhs._20) + (rhs._30);
	float transY = (x * rhs._01) + (y * rhs._11) + (z * rhs._21) + (rhs._31);
	float transZ = (x * rhs._02) + (y * rhs._12) + (z * rhs._22) + (rhs._32);
	float transW = (x * rhs._03) + (y * rhs._13) + (z * rhs._23) + (rhs._33);

	x = transX;
	y = transY;
	z = transZ;

    if (std::abs(transW - 1.0f) >= math::EPSILON)
    {
		float inv = 1.f / transW;

		x *= inv;
		y *= inv;
		z *= inv;
	}
#endif
}

void TVector3::TransformNormal(const TMatrix4x4& rhs) noexcept
{
#if TGON_SUPPORT_SSE
#else
	// Vector3's w element is '0'

	float transX = (x * rhs._00) + (y * rhs._10) + (z * rhs._20);
	float transY = (x * rhs._01) + (y * rhs._11) + (z * rhs._21);
	float transZ = (x * rhs._02) + (y * rhs._12) + (z * rhs._22);
	
	x = transX;
	y = transY;
	z = transZ;
#endif
}

} /* namespace math */
} /* namespace tgon */
