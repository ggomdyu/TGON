/**
 * @file    ThousandParty.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Core/Engine/Engine.h"

namespace tgon
{

class CameraComponent;
class SpriteRendererComponent;
class GraphicsModule;
class InputModule;
class TimeModule;

} /* namespace tgon */

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
    virtual ~ThousandParty() override {}

/**@section Public event handler */
public:
    virtual void OnDidLaunch() override;

    virtual void OnWillTerminate() override;

/**@section Public method */
public:
    virtual void Update() override;

    void Initialize();

    void InitializeModule();
};
