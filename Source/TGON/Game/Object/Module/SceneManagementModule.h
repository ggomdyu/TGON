/**
 * @filename    GraphicsModule.h
 * @author      ggomdyu
 * @since       07/24/2016
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
    SceneManagementModule(const VideoMode& videoMode, const std::shared_ptr<Window>& displayTarget);

/* @section Public destructor */
public:
    virtual ~SceneManagementModule() final override;

/* @section Public method */
public:
    virtual void Update() final override;
    
    void Draw();

    void ChangeScene(std::unique_ptr<Scene>&& scene);

    void SetDisplayTarget(const std::shared_ptr<Window>& displayTarget);
    
    std::weak_ptr<const Window> GetDisplayTarget() const noexcept;
    
    std::weak_ptr<Window>& GetDisplayTarget() noexcept;
    
    const Scene* GetCurrentScene() const noexcept;
    
    Scene* GetCurrentScene() noexcept;
    
/* @section Public method */
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
    
    std::weak_ptr<Window> m_displayTarget;
    
    SpriteBatch m_spriteBatch;

    std::unique_ptr<Scene> m_currScene;
};

} /* namespace tgon */
