/**
 * @filename    Drawing.h
 * @author      ggomdyu
 * @since       11/26/2017
 * @brief       Set of Low level Plaform-agnostic Drawing interfaces.
 */

#pragma once
#include "Core/Math/Point.h"

namespace tgon
{
namespace platform
{

void DrawPoint(const math::Point& p);

void DrawLine(const math::Point& p1, const math::Point& p2);

void DrawPolygon(const math::Point& p1, const math::Point& p2, const math::Point& p3);

} /* namespace platform */
} /* namespace tgon */
