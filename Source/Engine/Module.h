#pragma once

#include "Core/RuntimeObject.h"

namespace tg
{

enum class ModuleStage
{
    Idle,
    Update,
    Render,
};

class Module :
    public RuntimeObject
{
public:
    TGON_RTTI(Module)

/**@section Method */
public:
    /**
     * @brief   Initializes the object.
     */
    virtual void Initialize() {}

    /**
    * @brief   Updates the frame of the object.
    */
    virtual void Update() {}
};

template <typename _Module>
concept Moduleable = requires(_Module* module) {
    static_cast<Module*>(module);
    _Module::ModuleStage;
};

}
