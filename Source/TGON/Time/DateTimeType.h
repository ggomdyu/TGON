/**
 * @file    DateTimeType.h
 * @author  ggomdyu
 * @since   04/23/2017
 */

#pragma once

namespace tgon
{

enum class DateTimeKind
{
    Unspecified = 0x0,
    Local = 0x1,
    Utc = 0x2,
};

enum class DayOfWeek
{
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

} /* namespace tgon */
