/**
 * @file    View.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>
#include <map>

#include "Core/CoreObject.h"
#include "Core/DelegateChain.h"

#include "SpriteBatch.h"

namespace tgon
{

class Graphics;
class Camera;
class Sprite;
class Material;

class TGON_API View final :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(View);

/**@section Constructor */
public:
    View();
    
/**@section Method */
public:
    void Update();
    void Draw(Graphics& graphics);
    void AddSprite(const std::shared_ptr<Sprite>& sprite);
    void AddCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
private:
    void PrepareDefaultMaterials();
    void FlushSpriteBatches(Graphics& graphics);
    
/**@section Event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnResizeView;

/**@section Variable */
private:
    std::map<int32_t, std::vector<std::shared_ptr<Sprite>>> m_spriteLayer;
    std::shared_ptr<Material> m_uiMaterial;
    std::vector<SpriteBatch> m_spriteBatches;
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
