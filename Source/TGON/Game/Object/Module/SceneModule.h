/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include "Core/Object/Module/IModule.h"
#include "Graphics/LowLevel/Graphics.h"
#include "Graphics/Render/SpriteBatch.h"

namespace tgon
{

class Scene;

class TGON_API SceneModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(SceneModule);

/* @section Public constructor */
public:
    SceneModule(std::unique_ptr<Scene> scene, const VideoMode& videoMode, const Window& displayTarget);
    SceneModule(const VideoMode& videoMode, const Window& displayTarget);

/* @section Public destructor */
public:
    virtual ~SceneModule() final override;

/* @section Public method */
public:
    /* @brief   Updates the frame of scene. */
    virtual void Update() final override;
    
    /* @brief   Changes the current scene. */
    void ChangeScene(std::unique_ptr<Scene> scene);

    /**
     * @brief   Returns the current managed scene.
     * @return  The pointer to scene.
     */
    const Scene& GetCurrentScene() const noexcept;
    
    /**
     * @brief   Returns the current managed scene.
     * @return  The pointer to scene.
     */
    Scene& GetCurrentScene() noexcept;
    
/* @section Private method */
private:
    /* @brief   Draws the frame of Scene. */
    void Draw();

/* @section Private variable */
private:
    Graphics m_graphics;
    SpriteBatch m_spriteBatch;

    std::unique_ptr<Scene> m_currentScene;
};

} /* namespace tgon */
