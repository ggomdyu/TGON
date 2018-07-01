/**
 * @file    Graphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>

#include "Core/Platform/Config.h"

namespace tgon
{

struct Color4f;
class Window;
struct VideoMode;
enum class PrimitiveType;
enum class FillMode;
enum class CullMode;
class GraphicsImpl;

class Graphics final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Graphics(const Window& displayTarget, const VideoMode& videoMode);
    
/* @section Public destructor */
public:
    ~Graphics();

/* @section Public method */
public:
    void SetClearColor(const Color4f& color);
    void SetFillMode(FillMode fillMode);
    void SetCullMode(CullMode cullMode);
    void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
    void EnableBlend();
    void EnableDepthTest();
    void DisableBlend();
    void DisableDepthTest();
    void ClearColorBuffer();
    void ClearColorDepthBuffer();
    void SwapBuffer();
    void DrawPrimitives(PrimitiveType primitiveType, int32_t primitiveCount);
    void DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t primitiveCount);

/* @section Private variable */
private:
    std::unique_ptr<GraphicsImpl> m_graphicsImpl;
};

} /* namespace tgon */
