/**
 * @filename    IRuntimeObject.h
 * @author      ggomdyu
 * @since       10/29/2017
 */

#pragma once
#include "IRuntimeObjectType.h"

namespace tgon
{
namespace object
{

class IRuntimeObject
{
/* @section Public type */
public:
    using SuperType = void;
    using ThisType = IRuntimeObject;

/* @section Public method */
public:
    /* @brief   Get static bound type information. */
    template <typename _Type>
    friend const RTTI* GetRTTI();

    /* @brief   Get dynamic bound type information. */
    virtual const RTTI* GetRTTI() const = 0;
};

template <typename _Type>
inline const RTTI* GetRTTI()
{
    using PureType = std::remove_pointer_t<std::decay_t<_Type>>;

    static_assert(std::is_convertible<PureType*, IRuntimeObject*>::value, "GetRTTI only accepts template parameter that inherited from IRuntimeObject.");

    static const RTTI rtti(typeid(PureType), GetRTTI<typename PureType::SuperType>());
    return &rtti;
}

template <>
inline const RTTI* GetRTTI<void>()
{
    return nullptr;
}

} /* namespace object */
} /* namespace tgon */


#define TGON_RUNTIME_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::object::RTTI* GetRTTI() const override\
    {\
        return tgon::object::GetRTTI<classType>();\
    }
