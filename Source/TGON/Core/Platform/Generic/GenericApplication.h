/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * since        03/20/2016
 */

#pragma once
#include "GenericApplicationType.h"
#include "Core/Object/Object.h"

namespace tgon
{
namespace platform
{

class TGON_API GenericApplication :
    public object::TObject
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
    virtual void ShowTopStatusBar() = 0;
    virtual void HideTopStatusBar() = 0;
};

} /* namespace platform */
} /* namespace tgon */
