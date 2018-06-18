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

class TGON_API SceneManagementModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(SceneManagementModule);

/* @section Public constructor */
public:
    SceneManagementModule(std::unique_ptr<Scene> scene, const VideoMode& videoMode, std::shared_ptr<Window> displayTarget);
    SceneManagementModule(const VideoMode& videoMode, std::shared_ptr<Window> displayTarget);

/* @section Public destructor */
public:
    virtual ~SceneManagementModule() final override;

/* @section Public method */
public:
    /* @brief   Updates the frame of Scene. */
    virtual void Update() final override;
    
    /**/
    void ChangeScene(std::unique_ptr<Scene> scene);

    /**
     * @brief                       Sets the draw target window.
     * @param [in] displayTarget    The target window to draw.
     */
    void SetDisplayTarget(std::shared_ptr<Window> displayTarget);
    
    std::weak_ptr<const Window> GetDisplayTarget() const noexcept;
    
    std::weak_ptr<Window> GetDisplayTarget() noexcept;
    
    /**
     * @brief   Returns the current managed scene.
     * @return  The pointer to scene.
     */
    const Scene* GetCurrentScene() const noexcept;
    
    /**
     * @brief   Returns the current managed scene.
     * @return  The pointer to scene.
     */
    Scene* GetCurrentScene() noexcept;
    
/* @section Private method */
private:
    /* @brief   Draw the frame of Scene. */
    void Draw();

/* @section Private variable */
private:
    Graphics m_graphics;
    
    std::weak_ptr<Window> m_displayTarget;
    
    SpriteBatch m_spriteBatch;

    std::unique_ptr<Scene> m_currScene;
};

} /* namespace tgon */
