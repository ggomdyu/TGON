/**
 * @file    View.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <memory>

#include "Core/Object/CoreObject.h"
#include "Core/Object/DelegateChain.h"
#include "Graphics/LowLevel/Graphics.h"

#include "Batch.h"
#include "SpriteBatch.h"

namespace tgon
{

class Window;
struct VideoMode;

class TGON_API View final :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(View);

/**@section Public constructor */
public:

/**@section Public method */
public:
    void Draw(Graphics& graphics);
    
    /**@brief   Adds a SpriteBatch into the SpriteBatchGroup. */
    void AddSpriteBatch(const Color4f& blendColor, const std::shared_ptr<Sprite>& sprite, const std::shared_ptr<Material>& material, const Matrix4x4& matWorld);

    /**@brief   Adds a camera into View. */
    void AddCamera(const std::shared_ptr<Camera>& camera);

    /**@brief   Removes the specified camera in View. */
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
    std::vector<std::shared_ptr<Camera>>& GetCameraList() noexcept;

    const std::vector<std::shared_ptr<Camera>>& GetCameraList() const noexcept;

/**@section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnResizeView;

/**@section Private variable */
private:
    //BatchGroup m_batchGroup;

    SpriteBatchGroup m_spriteBatchGroup;
    
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
