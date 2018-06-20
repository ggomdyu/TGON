/**
 * @file    Object.h
 * @author  ggomdyu
 * @since   03/22/2016
 * @brief   Define class which becomes the base of all objects.
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <string>

#include "Runtime/RuntimeObject.h"
#include "Runtime/RuntimeObjectUtility.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(CoreObject);

/* @section Public constructor */
public:
    CoreObject() = default;

/* @section Public destructor */
public:
    virtual ~CoreObject() override = default;
};

} /* namespace tgon */
