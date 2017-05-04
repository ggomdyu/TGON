/**
 * @filename    GraphicsModule.h
 * @author   ggomdyu
 * since    04/03/2017
 */

#pragma once
#include "Interface/IModule.h"

namespace tgon
{

class TGON_API GraphicsModule :
	public IModule
{
public:
    TGON_MAKE_OBJECT_INTERFACE(GraphicsModule)

/**
 * @section Ctor/Dtor
 */
public:
	GraphicsModule();
	virtual ~GraphicsModule( );

/**
 * @section Public command method
 */
public:
	virtual void Update( );

/**
 * @section Get method
 */
public:
};

} /* namespace tgon */