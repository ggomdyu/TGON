#include "PrecompiledHeader.pch"
#include "../Drawing.h"

#include <Windows.h>

namespace tgon
{
namespace platform
{

void DrawPoint(const math::Point& p)
{
    SetPixel(nullptr, p.x, p.y, RGB(0, 0, 0));
}

void DrawLine(const math::Point& p1, const math::Point& p2)
{
}

void DrawPolygon(const math::Point& p1, const math::Point& p2, const math::Point& p3)
{
}

} /* namespace platform */
} /* namespace tgon */