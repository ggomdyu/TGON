/**
 * @filename    Drawing.h
 * @author      ggomdyu
 * @since       11/26/2017
 * @brief       The set of LLA plaform-agnostic drawing interfaces.
 */

#pragma once
#include "Core/Math/Point.h"

#include "Config.h"

namespace tgon
{

TGON_API void DrawPoint(const Point& p);

TGON_API void DrawLine(const Point& p1, const Point& p2);

TGON_API void DrawPolygon(const Point& p1, const Point& p2, const Point& p3);

} /* namespace tgon */