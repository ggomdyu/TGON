/**
 * @file    Random.h
 * @author  ggomdyu
 * @since   03/14/2016
 */

#pragma once
#include <cstddef>
#include <cstdint>

#include "Platform/Config.h"

namespace tgon
{

class Random
{
/**@section Constructor */
public:
    Random();

/**@section Destructor */
public:
    virtual ~Random() = default;

/**@section Method */
public:
    int32_t Next() noexcept;
    int32_t Next(int32_t maxValue) noexcept;
    int32_t Next(int32_t minValue, int32_t maxValue) noexcept;
    void NextBytes(std::byte* bytes, int32_t count) noexcept;
    double NextDouble() noexcept;
    double NextDouble(double minValue, double maxValue) noexcept;

protected:
    virtual double Sample() noexcept;
};

} /* namespace tgon */
