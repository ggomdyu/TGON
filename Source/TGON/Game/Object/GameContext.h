/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{

class TGON_API GameContext final
{
/* @section Private constructor */
private:
    GameContext() = default;
    
/* @section Public method */
public:
    static GameContext* GetInstance();
};

} /* namespace tgon */
