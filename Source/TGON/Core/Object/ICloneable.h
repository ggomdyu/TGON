/**
 * @filename    ICloneable.h
 * @author      ggomdyu
 * @since       10/28/2017
 * @brief       Interface class for virtual copy constructor.
 */

#pragma once
#include <memory>

namespace tgon
{

class ICloneable
{
/* @section Public method */
public:
    /* @brief   Returns copied one from this instance. */
    virtual std::shared_ptr<ICloneable> Clone() const = 0;
};

} /* namespace tgon */