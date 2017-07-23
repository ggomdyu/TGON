/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * since        03/20/2016
 */

#pragma once
#include "Core/Object/Object.h"

#include "GenericApplicationType.h"

namespace tgon
{
namespace platform
{

class TGON_API GenericApplication :
    public object::Object
{
public:
    TGON_MAKE_OBJECT_INTERFACE(tgon::platform::GenericApplication)

/**
 * @section Ctor/Dtor
 */
protected:
    GenericApplication() = default;
public:
    virtual ~GenericApplication() = default;

/**
 * @section Public method
 */
public:
    virtual void ShowTopStatusBar() {};
    virtual void HideTopStatusBar() {};
};

} /* namespace platform */
} /* namespace tgon */
