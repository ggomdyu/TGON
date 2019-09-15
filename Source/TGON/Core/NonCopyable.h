/**
 * @file    NonCopyable.h
 * @author  ggomdyu
 * @since   09/08/2019
 */

#pragma once

namespace tgon
{

class NonCopyable
{
/**@section Constructor */
public:
    constexpr NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;

/**@section Destructor */
public:
    ~NonCopyable() = default;

/**@section Operator */
public:
    NonCopyable& operator=(const NonCopyable&) = delete;
};

} /* namespace tgon */
