/**
 * @filename    GraphicsModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "Core/Object/Module/IModule.h"

#include "Graphics/LowLevelRender/Graphics.h"

namespace tgon
{

class TGON_API GraphicsModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule)

/* @section Public constructor */
public:
    GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& displayTargetWindow);

/* @section Public destructor */
public:
    virtual ~GraphicsModule() final override;

/* @section Public method */
public:
    virtual void Update() final override;
    void AddBatch(/*Batch* batch*/);
    void Draw();
    Graphics& GetGraphics();
    const Graphics& GetGraphics() const;

/* @section Public method */
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
};

} /* namespace tgon */