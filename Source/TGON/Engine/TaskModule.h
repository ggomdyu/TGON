/**
 * @file    TaskModule.h
 * @author  ggomdyu
 * @since   05/22/2019
 */

#pragma once
#include "IModule.h"

namespace tgon
{

class TGON_API TaskModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(TaskModule);

/**@section Constructor */
public:
    TaskModule();

/**@section Destructor */
public:
    virtual ~TaskModule() override = default;

/**@section Method */
public:
    virtual void Update() override;

/**@section Variable */
private:
};

} /* namespace tgon */
