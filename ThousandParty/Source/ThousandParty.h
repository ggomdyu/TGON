/**
 * @file    ThousandParty.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Engine/Engine.h"

class TGON_API ThousandParty final :
    public tgon::Engine
{
public:
    TGON_DECLARE_RTTI(ThousandParty)

/**@section Constructor */
public:
    ThousandParty() {}

/**@section Destructor */
public:
    virtual ~ThousandParty() override = default;

/**@section Event Handler */
public:
    virtual void OnLaunch() override;
    virtual void OnTerminate() override;

/**@section Method */
public:
    virtual void Update() override;

    void Initialize();
    void InitializeModule();
};
