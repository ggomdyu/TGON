/**
 * @filename    Random.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstddef>
#include <algorithm>
#include <random>

#include "Core/Random/WELLRNG.h"

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

/* @brief   Choices random element from container and return it as iterator. */
template <typename ContainerTy>
inline auto Choice(ContainerTy& container) -> typename ContainerTy::iterator
{
    auto iter = container.begin();
    std::advance(iter, Range(0, container.size() - 1));

    return iter;
}

/* @todo    Shuffles the given container. */
template <typename ContainerTy>
inline void Shuffle(ContainerTy& container)
{
    auto randomSeed = static_cast<unsigned int>(std::time(nullptr));
    std::shuffle(container.begin(), container.end(), std::default_random_engine(randomSeed));
};

} /* namespace random */
} /* namespace tgon */