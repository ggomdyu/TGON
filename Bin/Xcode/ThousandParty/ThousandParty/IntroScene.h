/**
 * @file    IntroScene.h
 * @author  ggomdyu
 * @since   09/29/2018
 */

#pragma once
#include <memory>

#include "Game/Scene.h"

namespace tgon
{

class GameObject;
class CameraComponent;
class SpriteRendererComponent;
class GraphicsModule;
class InputModule;
class TimeModule;

} /* namespace tgon */

class TGON_API IntroScene :
    public tgon::Scene
{
public:
    TGON_DECLARE_RTTI(IntroScene)
    
/**@section Constructor */
public:
    IntroScene();
    
/**@section Method */
public:
    virtual void Update() override;
    
/**@section Variable */
private:
    float camZ;

    std::shared_ptr<tgon::GameObject> m_nightSkyObject;
    std::shared_ptr<tgon::GraphicsModule> m_graphicsModule;
    std::shared_ptr<tgon::InputModule> m_inputModule;
    std::shared_ptr<tgon::TimeModule> m_timeModule;
    std::shared_ptr<tgon::CameraComponent> m_cameraComponent;
    std::shared_ptr<tgon::SpriteRendererComponent> m_fadeInSpriteComponent;
    std::shared_ptr<tgon::SpriteRendererComponent> m_nightSkySpriteComponent;
};
