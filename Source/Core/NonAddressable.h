#pragma once

namespace tg
{

class NonAddressable
{
/**@section Operator */
public:
    double operator&() const = delete;
};

}