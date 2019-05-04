/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Core/Engine/Module/IModule.h"

#include "../LowLevel/Graphics.h"
#include "../Render/SpriteBatch.h"

namespace tgon
{

class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(GraphicsModule);
    
/**@section Public constructor */
public:
    GraphicsModule(const std::shared_ptr<Window>& window, const VideoMode& videoMode);

/**@section Public destructor */
public:
    virtual ~GraphicsModule() override final = default;
    
/**@section Public method */
public:
    /**@brief   Updates this module. */
    virtual void Update() override;
    
    Graphics& GetGraphics() noexcept;
    
    const Graphics& GetGraphics() const noexcept;
    
    void AddCamera(const std::shared_ptr<Camera>& camera);
    
    /**@brief   Removes the specified camera in View. */
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
/**@section Private method */
private:
    /**@brief   Draws the render stage. */
    void Draw();

/**@section Private variable */
public:
    Graphics m_graphics;
    
    std::vector<std::shared_ptr<Camera>> m_cameraList;
    
    std::vector<SpriteBatch> m_spriteBatches;
};

} /* namespace tgon */
