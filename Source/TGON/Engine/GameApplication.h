/**
 * @filename    GameApplication.h
 * @author   ggomdyu
 * since    07/23/2016
 */

#pragma once
#include "../Engine/EngineContextObject.h"
#include "../Core/Platform/TWindow.h"


#define TGON_MAKE_GAME_APPLICATION(className)\
namespace tgon\
{\
std::shared_ptr<tgon::GameApplication> MakeGameApplication()\
{\
	return std::make_shared<className>();\
}\
}

namespace tgon
{

class TGON_API GameApplication :
    public object::TObject
{
public:
	TGON_MAKE_OBJECT_INTERFACE(GameApplication)

/**
 * @section Ctor/Dtor
 */ 
public:
    GameApplication(const std::shared_ptr<window::TWindow>& window /*= MakeWindow(WindowStyle{})*/);

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
    /* @brief   Resume the frame update */
    void ResumeUpdate() noexcept;

	/* @brief   Pause the frame update */
    void PauseUpdate() noexcept;

/**
 * @section Get method
 */ 
public:
    bool IsPaused() const noexcept;
    const std::shared_ptr<window::TWindow>& GetRootWindow() const noexcept;

/**
 * @section Private variable
 */ 
private:
	bool m_paused;
	std::shared_ptr<window::TWindow> m_rootWindow;
};

}