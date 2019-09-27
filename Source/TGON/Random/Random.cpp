#include "PrecompiledHeader.h"

#include <time.h>

#include "WELL1024a.h"
#include "Random.h"

namespace tgon
{

Random::Random()
{
    SrandWELL1024a();
}

int32_t Random::Next() noexcept
{
    return Next(0, INT32_MAX);
}

int32_t Random::Next(int32_t maxValue) noexcept
{
    return Next(0, maxValue);
}

int32_t Random::Next(int32_t minValue, int32_t maxValue) noexcept
{
    return minValue + int32_t(Sample() * double(maxValue - minValue));
}

void Random::NextBytes(std::byte* bytes, int32_t count) noexcept
{
    for (int32_t i = 0; i < count; ++i)
    {
        bytes[i] = std::byte(Next(0, 255));
    }
}

double Random::NextDouble() noexcept
{
    return Sample();
}

double Random::NextDouble(double minValue, double maxValue) noexcept
{
    return minValue + (Sample() * (maxValue - minValue));
}

double Random::Sample() noexcept
{
    return WELL1024a();
}

} /* namespace tgon */