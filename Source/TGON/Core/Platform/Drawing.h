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
namespace core
{

void DrawPoint(const core::Point& p);

void DrawLine(const core::Point& p1, const core::Point& p2);

void DrawPolygon(const core::Point& p1, const core::Point& p2, const core::Point& p3);

} /* namespace core */
} /* namespace tgon */
