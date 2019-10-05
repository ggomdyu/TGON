/**
 * @file    LogoScene.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Game/Scene.h"
#include "Engine/InputModule.h"
#include "Engine/TimeModule.h"

class TGON_API LogoScene :
    public tgon::Scene
{
public:
    TGON_DECLARE_RTTI(LogoScene)

/**@section Constructor */
public:
    LogoScene();
    
/**@section Method */
public:
    void Initialize();
    virtual void Update() override;
    
private:
    void InitializeGraphics();
    void CreateGameObjects();
    void CreateCameraObject();
    void CreateFontObject();
    
    void OnHandleInput();

/**@section Variable */
private:
    std::shared_ptr<tgon::InputModule> m_inputModule;
    std::shared_ptr<tgon::TimeModule> m_timeModule;
};
