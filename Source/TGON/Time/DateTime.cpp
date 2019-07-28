#include "PrecompiledHeader.h"

#include "TimeZoneInfo.h"
#include "DateTime.h"

namespace tgon
{

DateTime DateTime::ToUniversalTime() const
{
    return TimeZoneInfo::ConvertTimeToUtc(*this);
}

} /* namespace tgon */
