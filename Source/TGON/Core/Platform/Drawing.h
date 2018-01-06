/**
 * @filename    Drawing.h
 * @author      ggomdyu
 * @since       11/26/2017
 * @brief       Set of Low level Plaform-agnostic Drawing interfaces.
 */

#pragma once
#include "Config.h"

#include "Core/Math/Point.h"

namespace tgon
{
namespace core
{

TGON_API void DrawPoint(const core::Point& p);

TGON_API void DrawLine(const core::Point& p1, const core::Point& p2);

TGON_API void DrawPolygon(const core::Point& p1, const core::Point& p2, const core::Point& p3);

} /* namespace core */
} /* namespace tgon */
