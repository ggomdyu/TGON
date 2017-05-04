#include "PrecompiledHeader.h"
#include "TQuaternion.h"

#include "TMatrix4x4.h"

namespace tgon {
namespace math {

const TQuaternion TQuaternion::Zero;
const TQuaternion TQuaternion::Identity( 0.f, 0.f, 0.f, 1.f );

TMatrix4x4 TQuaternion::RotateMatrix() const
{
	return TMatrix4x4(
        1.f - 2.0f*y*y -2.f*z*z,
        2.f*x*y - 2.f*w*z,
        2.f*x*z + 2.f*w*y,
		0.f,

        2.f*x*y + 2.0f*w*z,
        1.f - 2.0f*x*x - 2.0f*z*z,
        2.f*y*z - 2.0f*w*x,
		0.f,

        2.f*x*z - 2.0f*w*y,
        2.f*y*z + 2.0f*w*x,
        1.f -2.f*x*x -2.f*y*y,
		0.f,

		0.f,
		0.f,
		0.f,
		1.f
    );
}

} /* namespace math */
} /* namespace tgon */
