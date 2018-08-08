#include "PrecompiledHeader.h"

#include "DateTime.h"

namespace tgon
{

DateTime DateTime::Today()
{
    DateTime today = DateTime::Now();
    {
        today.m_hour = 0;
        today.m_minute = 0;
        today.m_second = 0;
    }
    return today;
}

void DateTime::AddDays(int days)
{
    this->AddDays(static_cast<float>(days));
}

} /* namespace tgon */
