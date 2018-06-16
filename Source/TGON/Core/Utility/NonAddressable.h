/**
 * @filename    NonAddressable.h
 * @author      ggomdyu
 * @since       06/16/2018
 */

#pragma once

namespace tgon
{

class NonAddressable
{
/* @section Public operator */
public:
    double operator&() const = delete;
};

} /* namespace tgon */