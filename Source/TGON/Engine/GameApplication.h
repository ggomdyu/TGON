/**
 * filename GameApplication.h
 * author   ggomdyu
 * since    07/23/2016
 */

#pragma once
#include "../Engine/EngineContextObject.h"
#include "../Core/Platform/TWindow.h"


#define TGON_GENERATE_GAMEAPP( className )\
namespace tgon {\
	std::shared_ptr<tgon::GameApplication> GenerateGameApplication( )\
	{\
		return std::make_shared<className>( );\
	}\
}

namespace tgon
{

class TGON_API GameApplication :
	public TObject
{
public:
	TGON_MAKE_OBJECT_INTERFACE(GameApplication)

/**
 * @section Ctor/Dtor
 */ 
public:
    GameApplication(const std::shared_ptr<TWindowFrame>& window /*= MakeWindow(WindowStyle{})*/);

/**
 * @section Public command methods
 */
public:
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

/**
 * @section Set methods
 */ 
public:
    /* @brief   Resume the frame update */
    void ResumeUpdate() noexcept;

	/* @brief   Pause the frame update */
    void PauseUpdate() noexcept;

/**
 * @section Get methods
 */ 
public:
    bool IsPaused() const noexcept;
    const std::shared_ptr<TWindowFrame>& GetRootWindow() const noexcept;

/**
 * @section Private variables
 */ 
private:
	bool m_paused;
	std::shared_ptr<TWindowFrame> m_rootWindow;
};

}