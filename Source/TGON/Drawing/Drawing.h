/**
 * @file    Drawing.h
 * @author  ggomdyu
 * @since   11/26/2017
 * @brief   Set of Low level Plaform-agnostic Drawing interfaces.
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Point.h"
#include "Platform/Window.h"

namespace tgon
{

TGON_API void DrawPoint(Window& window, const Point& p);

TGON_API void DrawLine(Window& window, const Point& p1, const Point& p2);

TGON_API void DrawPolygon(Window& window, const Point& p1, const Point& p2, const Point& p3);

} /* namespace tgon */
