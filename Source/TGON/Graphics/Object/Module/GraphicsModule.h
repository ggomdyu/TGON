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
    TGON_RUNTIME_OBJECT(GraphicsModule);

/* @section Public constructor */
public:
    GraphicsModule(const VideoMode& videoMode, Window& displayTargetWindow);

/* @section Public destructor */
public:
    virtual ~GraphicsModule() final override;

/* @section Public method */
public:
    virtual void Update() final override;
    void Draw();
//    void AddBatch(const Batch& batch);
//    void AddBatch(Batch&& batch);
//    void AddSpriteBatch(const SpriteBatch& spriteBatch);
//    void AddSpriteBatch(SpriteBatch&& spriteBatch);
    Graphics& GetGraphics();
    const Graphics& GetGraphics() const;

/* @section Public method */
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
    
//    std::vector<Batch> m_batches;
//    std::vector<SpriteBatch> m_spriteBatches;
};

} /* namespace tgon */
