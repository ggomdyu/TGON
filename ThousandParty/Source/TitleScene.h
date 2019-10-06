/**
 * @file    TitleScene.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Game/Scene.h"
#include "Game/GameObject.h"
#include "Engine/InputModule.h"
#include "Engine/TimeModule.h"

class TGON_API TitleScene :
    public tgon::Scene
{
public:
    TGON_DECLARE_RTTI(TitleScene)

/**@section Constructor */
public:
    TitleScene();
    
/**@section Method */
public:
    void Initialize();
    virtual void Update() override;
    
private:
    void InitializeGraphics();
    void CreateGameObjects();
    void CreateFontObjects();
    void CreateUIObjects();
    void CreateFireFlyObjects();
    
    void OnHandleInput();

/**@section Variable */
private:
    std::shared_ptr<tgon::InputModule> m_inputModule;
    std::shared_ptr<tgon::TimeModule> m_timeModule;
    std::shared_ptr<tgon::UISprite> m_fadeInSprite;
    std::shared_ptr<tgon::GameObject> m_nightSky;
};
