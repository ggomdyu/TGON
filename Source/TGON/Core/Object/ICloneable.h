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
namespace core
{

class ICloneable
{
/* @section Public destructor */
public:
    virtual ~ICloneable() = 0;

/* @section Public method */
public:
    /* @brief   Returns copied one from this instance. */
    virtual std::shared_ptr<ICloneable> Clone() const { return nullptr; }
};

inline ICloneable::~ICloneable() = default;

} /* namespace core */
} /* namespace tgon */