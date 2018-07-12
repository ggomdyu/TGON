/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include "Core/Object/Module/IModule.h"
#include "Graphics/Render/Renderer.h"
#include "Graphics/Render/Camera.h"
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
    SceneModule(std::unique_ptr<Scene> scene, Window& displayTarget, const VideoMode& videoMode);
    SceneModule(Window& displayTarget, const VideoMode& videoMode);

/* @section Public destructor */
public:
    virtual ~SceneModule() final override;

/* @section Public method */
public:
    /* @brief   Updates the frame of scene. */
    virtual void Update() final override;
    
    void AddCamera(const Camera& camera);
    
    void RemoveCamera(const Camera& camera);
    
    /* @brief   Changes the current scene. */
    void ChangeScene(std::unique_ptr<Scene> scene);

    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    const Scene& GetCurrentScene() const noexcept;
    
    /**
     * @brief   Returns the current managed scene.
     * @return  The reference to scene.
     */
    Scene& GetCurrentScene() noexcept;
    
/* @section Private method */
private:
    /* @brief   Draws the frame of Scene. */
    void Draw();

/* @section Private variable */
private:
    Renderer m_renderer;
    SpriteBatch m_spriteBatch;
    
    std::vector<Camera> m_cameras;
    
    std::unique_ptr<Scene> m_currentScene;
};

} /* namespace tgon */