/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include "GameObject.h"

namespace tgon
{

class Scene :
    public GameObject
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Method */
public:
    virtual void OnStart() {}
    virtual void OnFinish() {}
};

} /* namespace tgon */