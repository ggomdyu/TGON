/**
 * @file    IModule.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Object.h"

namespace tgon
{

class TGON_API IModule :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(IModule);

/* @section Public destructor */
public:
    virtual ~IModule() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
};
    
inline IModule::~IModule() = default;

} /* namespace tgon */
