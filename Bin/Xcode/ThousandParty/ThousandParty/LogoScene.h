/**
 * @file    LogoScene.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Game/Scene/GameScene.h"

namespace tgon
{

class CameraComponent;
class SpriteRendererComponent;
class GraphicsModule;
class InputModule;
class TimeModule;

} /* namespace tgon */

class TGON_API LogoScene :
    public tgon::GameScene
{
public:
    TGON_DECLARE_RTTI(LogoScene);

/**@section Constructor */
public:
    LogoScene();
    
/**@section Method */
public:
    virtual void Update() override;
    
    void OnHandleInput();

/**@section Variable */
private:
    int64_t m_beginTime;
    std::shared_ptr<tgon::CameraComponent> m_cameraComponent;
    std::shared_ptr<tgon::SpriteRendererComponent> m_introSpriteComponent1;
    std::shared_ptr<tgon::SpriteRendererComponent> m_introSpriteComponent2;
    std::shared_ptr<tgon::SpriteRendererComponent> m_fadeOutSpriteComponent;
    std::shared_ptr<tgon::GraphicsModule> m_graphicsModule;
    std::shared_ptr<tgon::InputModule> m_inputModule;
    std::shared_ptr<tgon::TimeModule> m_timeModule;
};