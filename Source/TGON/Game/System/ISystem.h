/**
 * @filename    ISystem.h
 * @author      ggomdyu
 * @since       07/13/2016
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Object.h"

namespace tgon
{

class TGON_API ISystem :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(ISystem)

/* @section Public constructor */
public:
    ISystem() = default;
    ISystem(ISystem&& rhs) = delete;

/* @section Public destructor */
public:
    virtual ~ISystem() override = 0;

/* @section Public operator */
public:
    ISystem& operator=(ISystem&& rhs) = delete;

/* @section Public method */
public:
    virtual void Update() = 0;
};

inline ISystem::~ISystem() = default;

} /* namespace tgon */