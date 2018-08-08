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
    Unspecified,
    Local,
    Utc,
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
