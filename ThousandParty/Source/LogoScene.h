/**
 * @file    LogoScene.h
 * @author  ggomdyu
 * @since   10/06/2019
 */

#pragma once
#include <memory>

#include "Game/Scene.h"
#include "Component/SpriteRendererComponent.h"
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
    void CreateUIObject();
    
    void OnHandleInput();

/**@section Variable */
private:
    int64_t m_beginTime;
    std::shared_ptr<tgon::InputModule> m_inputModule;
    std::shared_ptr<tgon::TimeModule> m_timeModule;
    std::shared_ptr<tgon::UISprite> m_logoImages[3];
};
