/**
 * @filename    IModule.h
 * @author      ggomdyu
 * @since       07/13/2016
 */

#pragma once
#include "./Core/Object/TObject.h"

#include <boost/noncopyable.hpp>


namespace tgon
{

class TGON_API IModule :
    public object::TObject,
	private boost::noncopyable
{
public:
    TGON_CREATE_OBJECT_INTERFACE(IModule)

/**
 * @section Ctor/Dtor
 */
public:
    IModule();
    virtual ~IModule() = 0;

/**
 * @section Public command method
 */
public:
    virtual void Update() = 0;
};

}