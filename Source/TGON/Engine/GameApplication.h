/**
 * @filename    GameApplication.h
 * @author      ggomdyu
 * @since       07/23/2016
 */

#pragma once
#include "Engine/EngineContextObject.h"
#include "Core/Platform/Window.h"

#ifdef FindWindow
#   undef FindWindow
#endif

#define TGON_MAKE_GAME_APPLICATION(className)\
namespace tgon {\
std::shared_ptr<tgon::GameApplication> MakeGameApplication()\
{\
	return std::make_shared<className>();\
}\
} /* namespace tgon */

namespace tgon
{

class TGON_API GameApplication :
    public object::Object
{
public:
	TGON_OBJECT(tgon::GameApplication)

/**
 * @section Ctor/Dtor
 */ 
public:
    GameApplication(const platform::SharedWindow& window /*= MakeWindow(WindowStyle{})*/);

/**
 * @section Public command method
 */
public:
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

/**
 * @section Set method
 */ 
public:
	/* @brief   Pause the frame update */
    void PauseUpdate() noexcept;

    /* @brief   Resume the frame update */
    void ResumeUpdate() noexcept;

/**
 * @section Get method
 */ 
public:
    const platform::SharedWindow& GetRootWindow() const noexcept;
    
    bool IsPaused() const noexcept;

/**
 * @section Private variable
 */ 
private:
    platform::SharedWindow m_rootWindow;
	
    bool m_paused;
};

}