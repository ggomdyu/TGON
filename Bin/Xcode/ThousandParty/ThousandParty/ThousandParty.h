/**
 * @file    ThousandParty.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Core/Engine/Engine.h"

class TGON_API ThousandParty final :
    public tgon::Engine
{
public:
    TGON_DECLARE_RTTI(ThousandParty);

/**@section Public constructor */
public:
    ThousandParty() {}

/**@section Public destructor */
public:
    virtual ~ThousandParty() override = default;

/**@section Public event handler */
public:
    virtual void OnLaunch() override;
    virtual void OnTerminate() override;

/**@section Public method */
public:
    virtual void Update() override;

    void Initialize();
    void InitializeModule();
};
