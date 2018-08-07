#include "PrecompiledHeader.h"

#include "DateTime.h"

namespace tgon
{

DateTime DateTime::Today() noexcept
{
    DateTime today = DateTime::Now();
    {
        today.m_hour = 0;
        today.m_minute = 0;
        today.m_second = 0;
    }
    return today;
}

} /* namespace tgon */
