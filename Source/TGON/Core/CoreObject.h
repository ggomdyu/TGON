/**
 * @file    CoreObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "RuntimeObject.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(CoreObject)
};

} /* namespace tgon */
