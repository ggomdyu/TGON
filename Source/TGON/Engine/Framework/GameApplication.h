/**
 * @filename    Engine.h
 * @author      ggomdyu
 * @since       07/23/2016
 */

#pragma once
//#include "Core/Platform/Window.h"


namespace tgon
{
namespace engine
{

class GameApplication
{
/* @section Public method */
public:
    virtual void OnDraw() {};
    virtual void OnUpdate(float deltaTime) {};

/* @section Private variable */
private:
    bool m_isPaused;
};

} /* namespace engine */
} /* namespace tgon */
