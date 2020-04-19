#pragma once

namespace tg
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

}
