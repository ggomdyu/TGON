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
/* @section Public destructor */
public:
    virtual ~ICloneable() = default;

/* @section Public method */
public:
    /**
     * @brief   Returns copied one from instance.
     * @return  The instance copied from instance.
     */
    std::shared_ptr<const ICloneable> Clone() const;

    /**
     * @brief   Returns copied one from instance.
     * @return  The instance copied from instance.
     */
    virtual std::shared_ptr<ICloneable> Clone() = 0;
};

} /* namespace tgon */
