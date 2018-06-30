/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <memory>

namespace tgon
{
    
class Graphics;
class Window;
struct VideoMode;

class Renderer final
{
/* @section Public constructor */
public:
//    Renderer(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);

/* @section Public method */
public:

/* @section Private method */
private:
/* @section Private variable */
public:
    std::unique_ptr<Graphics> m_graphics;
};

} /* namespace tgon */
