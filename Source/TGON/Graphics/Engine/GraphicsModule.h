/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <vector>

#include "Core/Object/DelegateChain.h"
#include "Core/Math/Rect.h"
#include "Core/Engine/IModule.h"

#include "../Render/Camera.h"
#include "../Render/Scene.h"
#include "../LowLevel/Graphics.h"

namespace tgon
{
    
class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule);
    
/* @section Public constructor */
public:
    GraphicsModule(Window& window, const VideoMode& videoMode);

/* @section Public destructor */
public:
    virtual ~GraphicsModule() override = default;
    
/* @section Public method */
public:
    virtual void Update() override;
    
    void AddCamera(const Camera& camera);
    
    std::vector<Camera>& GetCameraList() noexcept;
    
    const std::vector<Camera>& GetCameraList() const noexcept;
    
    Graphics& GetGraphics() noexcept;
    
    const Graphics& GetGraphics() const noexcept;
    
/* @section Private method */
private:
    void Draw();
    
/* @section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnWindowResize;

/* @section Private variable */
public:
    Graphics m_graphics;
    
    I32Rect m_viewPort;
    
    std::vector<Camera> m_cameraList;
    
//    Scene m_scene;
};

} /* namespace tgon */
