/**
 * @filename    Random.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstddef>
#include <algorithm>
#include <random>

#include "Core/Random/WELL1024a.h"

namespace tgon
{
namespace random
{

/* @return  Random value between min to max */
inline float Range(float min, float max)
{
    return min + (static_cast<float>(WELLRNG1024a()) * (max - min));
}

/* @return  Random value between min to max */
inline int32_t Range(int32_t min, int32_t max)
{
    return static_cast<int32_t>(Range(static_cast<float>(min), static_cast<float>(max + 1)));
}

/* @brief   Choice random element from container and return it as a iterator. */
template <typename _ContainerType>
inline auto Choice(_ContainerType& container) -> typename _ContainerType::iterator
{
    auto iter = container.begin();
    std::advance(iter, Range(0, container.size() - 1));

    return iter;
}

/* @todo    Shuffle the given container. */
template <typename _ContainerType>
inline void Shuffle(_ContainerType& container)
{
    auto randomSeed = static_cast<unsigned int>(std::time(nullptr));
    std::shuffle(container.begin(), container.end(), std::default_random_engine(randomSeed));
};

} /* namespace random */
} /* namespace tgon */
