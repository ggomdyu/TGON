/**
 * @filename    Direct3D11DynamicGraphics.h
 * @author      ggomdyu
 * @since       02/23/2018
 */

#pragma once
#include "D3D11DynamicGraphicsFwd.h"

#include "../IDynamicGraphics.h"

#include "Core/Utility/Windows/COMPtr.h"

#include <memory>
#include <d3d11.h>

namespace tgon
{
namespace graphics
{
//
//constexpr GLenum ConvertFillModeToNative(FillMode fillMode) noexcept
//{
//    constexpr GLenum nativeFillModeTable[] =
//    {
//        GL_POINT,
//        GL_LINE,
//        GL_FILL
//    };
//
//    return nativeFillModeTable[static_cast<std::size_t>(fillMode)];
//}
//
//constexpr GLenum ConvertCullModeToNative(CullMode cullMode) noexcept
//{
//    constexpr GLenum nativeCullModeTable[] =
//    {
//        GL_CW,
//        GL_CCW
//    };
//
//    return nativeCullModeTable[static_cast<std::size_t>(cullMode)];
//}
//
//constexpr GLenum ConvertPrimitiveTypeToNative(PrimitiveType primitiveType) noexcept
//{
//    constexpr GLenum nativePrimitiveTypeTable[] =
//    {
//        GL_POINTS,
//        GL_LINES,
//        GL_LINE_STRIP,
//        GL_TRIANGLES,
//        GL_TRIANGLE_STRIP,
//        GL_TRIANGLE_FAN,
//    };
//
//    return nativePrimitiveTypeTable[static_cast<std::size_t>(primitiveType)];
//}

class D3D11DynamicGraphics :
    public IDynamicGraphics
{
/* @section Public constructor */
public:
    D3D11DynamicGraphics(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);
    virtual ~D3D11DynamicGraphics() override;

/* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) final override;
    virtual void SetCullMode(CullMode cullMode) final override;
    virtual void SetScissorRect(const core::FRect& rect) final override {}
    virtual void EnableBlend() final override;
    virtual void EnableDepthTest() final override;
    virtual void DisableBlend() final override;
    virtual void DisableDepthTest() final override;
    virtual void ClearColorBuffer() final override;
    virtual void ClearColorDepthBuffer() final override;
    virtual void SwapBuffer() final override;

/* @section Private method */
private:
    bool Initialize(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);
    bool InitializeD3D(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);
    
    bool CreateDXGIObjects(IDXGIFactory** dxgiFactory, IDXGIAdapter** dxgiAdapter, IDXGIOutput** dxgiAdapterOutput);
    bool EnumerateDisplayModes(IDXGIOutput* dxgiAdapterOutput, DXGI_FORMAT enumFormat, std::vector<DXGI_MODE_DESC>* displayModes);
    bool FindSuitDisplayMode(IDXGIOutput* dxgiAdapterOutput, DXGI_FORMAT requiredFormat, DXGI_MODE_DESC* suitDisplayMode);
    bool CreateDeviceAndSwapChain(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode, const DXGI_MODE_DESC& suitDispalyMode, ID3D11Device** device, ID3D11DeviceContext** deviceContext, IDXGISwapChain** m_swapChain);
    bool CreateRenderTargetView(ID3D11Device* device, IDXGISwapChain* swapChain, ID3D11RenderTargetView** renderTargetView);
    bool CreateDepthStencilBuffer(ID3D11Device* device, ID3D11Texture2D** depthStencilBuffer);
    bool CreateDepthStencilState(ID3D11Device* device, ID3D11DepthStencilState** depthStencilState);
    bool CreateDepthStencilView(ID3D11Device* device, ID3D11Texture2D* depthStencilBuffer, ID3D11DepthStencilView** depthStencilView);
    bool CreateRasterizerState(ID3D11Device* device, ID3D11RasterizerState** rasterizerState);
    
    void SetViewport(ID3D11DeviceContext* deviceContext, int32_t width, int32_t height, float minDepth, float maxDepth, float topLeftX, float topLeftY);

/* @section Private variable */
private:
    core::COMPtr<ID3D11Device> m_device;
    core::COMPtr<ID3D11DeviceContext> m_deviceContext;
    core::COMPtr<ID3D11RenderTargetView> m_renderTargetView;
    core::COMPtr<IDXGISwapChain> m_swapChain;
    core::COMPtr<ID3D11DepthStencilState> m_depthStencilState;
    core::COMPtr<ID3D11Texture2D> m_depthStencilBuffer;
    core::COMPtr<ID3D11DepthStencilView> m_depthStencilView;
    core::COMPtr<ID3D11RasterizerState> m_rasterizerState;

    FLOAT m_clearColor[4];
    UINT m_presentSyncInterval;
};

} /* namespace graphics */
} /* namespace tgon */