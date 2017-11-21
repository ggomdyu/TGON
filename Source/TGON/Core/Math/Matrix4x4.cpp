#include "PrecompiledHeader.pch"
#include "Matrix4x4.h"

#include "Matrix3x3.h"
#include "Vector3.h"

namespace tgon {
namespace math {

const TMatrix4x4 TMatrix4x4::Identity(
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f);

const TMatrix4x4 TMatrix4x4::Zero(
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f);


} /* namespace math */
} /* namespace tgon */
