/**
 * @filename    Random.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstddef>
#include <algorithm>
#include <random>
#include <time.h>
#include <type_traits>

#include "WELL1024a.h"

namespace tgon
{

/* @brief   Returns random value between min to max */
template <typename _ValueType,
    typename std::enable_if_t<std::is_floating_point<_ValueType>::value>* = nullptr>
inline _ValueType RandRange(_ValueType min, _ValueType max)
{
    return min + (static_cast<_ValueType>(WELL1024a()) * (max - min));
}

/* @brief   Returns random value between min to max */
template <typename _ValueType,
    typename std::enable_if_t<std::is_integral<_ValueType>::value>* = nullptr>
inline _ValueType RandRange(_ValueType min, _ValueType max)
{
    using FloatType = typename std::conditional<sizeof(_ValueType) == sizeof(float), float,
                      typename std::conditional<sizeof(_ValueType) == sizeof(double), double, void>::type>::type;

    return static_cast<_ValueType>(RandRange(static_cast<FloatType>(min), static_cast<FloatType>(max + 1)));
}

/* @brief   Choose a random element from the given container and return it as a iterator. */
template <typename _ContainerType>
inline typename _ContainerType::iterator Choice(_ContainerType& container)
{
    auto iter = container.begin();
    std::advance(iter, RandRange<_ContainerType::size_type>(0, container.size() - 1));

    return iter;
}

/* @brief   Choose a random element from the given container and return it as a iterator. */
template <typename _ContainerType>
inline typename _ContainerType::IteratorType Choice(_ContainerType& container)
{
    auto iter = container.begin();
    std::advance(iter, RandRange<_ContainerType::SizeType>(0, container.Size() - 1));

    return iter;
}

/* @brief   Shuffles the given container. */
template <typename _ContainerType>
inline void Shuffle(_ContainerType& container)
{
    auto randomSeed = static_cast<unsigned int>(time(nullptr));
    std::shuffle(container.begin(), container.end(), std::default_random_engine(randomSeed));
};

} /* namespace tgon */
