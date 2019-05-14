/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include <memory>
#include <vector>

#include "Platform/Config.h"

namespace tgon
{
    
class CanvasSprite;
class Material;
class Camera;
class Graphics;

class TGON_API MeshRenderer
{
/**@section Method */
public:
    void Update();
    void Draw(Graphics& graphics);
    void AddCamera(const std::shared_ptr<Camera>& camera);
    bool RemoveCamera(const std::shared_ptr<Camera>& camera);
    
/**@section Variable */
public:
    std::vector<std::shared_ptr<Camera>> m_cameraList;
};

} /* namespace tgon */
