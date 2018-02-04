#include "PrecompiledHeader.pch"

#include "D3D11DynamicGraphics.h"

#include "../GraphicsType.h"

#include "Core/Debug/Log.h"
#include "Core/Platform/Window.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace tgon
{
namespace graphics
{

D3D11DynamicGraphics::D3D11DynamicGraphics(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode) :
    m_swapChainSyncInterval(videoMode.enableVerticalSync ? 1 : 0),
    m_clearColor{videoMode.clearColor.r, videoMode.clearColor.g, videoMode.clearColor.b, videoMode.clearColor.a}
{
    this->InitializeD3D(window, videoMode);

    this->SetClearColor(videoMode.clearColor);
}

D3D11DynamicGraphics::~D3D11DynamicGraphics()
{
    // 종료하기 전에 이렇게 윈도우 모드로 바꾸지 않으면 스왑체인을 할당 해제할 때 예외가 발생합니다.
    /*if (m_swapChain)
    {
        m_swapChain->SetFullscreenState(false, NULL);
    }*/
}

bool D3D11DynamicGraphics::InitializeD3D(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode)
{
    // Create a DXGI factory that you can use to generate other DXGI objects.
    core::COMPtr<IDXGIFactory> dxgiFactory;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory))))
    {
        core::Log("Failed to invoke CreateDXGIFactory.");
        return false;
    }

    // Enumerate the video cards.
    core::COMPtr<IDXGIAdapter> dxgiAdapter;
    if (FAILED(dxgiFactory->EnumAdapters(0, &dxgiAdapter)))
    {
        core::Log("Failed to invoke IDXGIFactory::EnumAdapters.");
        return false;
    }

    // Enumerate adapter outputs.
    core::COMPtr<IDXGIOutput> dxgiAdapterOutput;
    if (FAILED(dxgiAdapter->EnumOutputs(0, &dxgiAdapterOutput)))
    {
        core::Log("Failed to invoke IDXGIAdapter::EnumOutputs.");
        return false;
    }

    //// Find suitable Display Mode
    // Get the number of display modes which suitable for R8G8B8A8 format.
    UINT numModes;
    if (FAILED(dxgiAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr)))
    {
        core::Log("Failed to invoke IDXGIOutput::GetDisplayModeList.");
        return false;
    }

    // Then, list those display modes to displayModes.
    std::vector<DXGI_MODE_DESC> displayModes(numModes);
    if (FAILED(dxgiAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes.data())))
    {
        core::Log("Failed to invoke IDXGIOutput::GetDisplayModeList.");
        return false;
    }

    int32_t windowWidth, windowHeight;
    window->GetSize(&windowWidth, &windowHeight);

    DXGI_MODE_DESC suitDisplayMode;
    for (const auto& displayMode : displayModes)
    {
        if (displayMode.Width == static_cast<UINT>(windowWidth) &&
            displayMode.Height == static_cast<UINT>(windowHeight))
        {
            suitDisplayMode = displayMode;
            break;
        }
    }

    //// Creation of Swap Chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc {};
    swapChainDesc.OutputWindow = reinterpret_cast<HWND>(window->GetNativeWindow());
    swapChainDesc.Windowed = true;
    swapChainDesc.BufferCount = 1; // Back buffer count is 1
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferDesc.Width = windowWidth;
    swapChainDesc.BufferDesc.Height = windowHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard back buffer after drawing

    if (videoMode.enableVerticalSync)
    {
        swapChainDesc.BufferDesc.RefreshRate = suitDisplayMode.RefreshRate;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }

    if (videoMode.enableMultiSampling)
    {
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        /*swapChainDesc.SampleDesc.Count = videoMode.sampleCount;
        swapChainDesc.SampleDesc.Quality = 100;*/
    }
    else
    {
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
    }

    // We're going to use DirectX version 11.
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
    D3D_DRIVER_TYPE driverType = (videoMode.enableHardwareAccelerate) ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_SOFTWARE;
    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, nullptr, &m_deviceContext)))
    {
        core::Log("Failed to invoke D3D11CreateDeviceAndSwapChain.");
        return false;
    }

    //// Create a Back buffer and Connect it to swap chain
    core::COMPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
    {
        core::Log("Failed to invoke IDXGISwapChain::GetBuffer.");
        return false;
    }

    if (FAILED(m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView)))
    {
        core::Log("Failed to invoke ID3D11Device::CreateRenderTargetView.");
        return false;
    }

    //// Create a Depth buffer
    D3D11_TEXTURE2D_DESC depthBufferDesc {};
    depthBufferDesc.Width = windowWidth;
    depthBufferDesc.Height = windowHeight;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    if (FAILED(m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer)))
    {
        core::Log("Failed to invoke ID3D11Device::CreateTexture2D.");
        return false;
    }

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc {};
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xff;
    depthStencilDesc.StencilWriteMask = 0xff;
    // Stencil operations if pixel is front-facing.
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    
    // Stencil operations if pixel is back-facing.
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    if (FAILED(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState)))
    {
        core::Log("Failed to invoke ID3D11Device::CreateTexture2D.");
        return false;
    }

    // Register created depth stencil state to DeviceContext.
    m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

    // Now we will make depth stencil view. We must create it because Direct3D appreciate the depth stencil buffer is texture after do this.
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc {};
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView)))
    {
        core::Log("Failed to invoke ID3D11Device::CreateDepthStencilView.");
        return false;
    }

    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    D3D11_RASTERIZER_DESC rasterizerDesc {};
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0;

    if (FAILED(m_device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState)))
    {
        core::Log("Failed to invoke ID3D11Device::CreateRasterizerState.");
        return false;
    }

    m_deviceContext->RSSetState(m_rasterizerState);

    D3D11_VIEWPORT viewportDesc{};
    viewportDesc.Width = windowWidth;
    viewportDesc.Height = windowHeight;
    viewportDesc.MinDepth = 0.0f;
    viewportDesc.MaxDepth = 1.0f;
    viewportDesc.TopLeftX = 0.0f;
    viewportDesc.TopLeftY = 0.0f;

    m_deviceContext->RSSetViewports(1, &viewportDesc);

    float fieldOfView, screenAspect;

}

void D3D11DynamicGraphics::SetClearColor(const core::Color4f& color)
{
}

void D3D11DynamicGraphics::SetFillMode(FillMode fillMode)
{
}

void D3D11DynamicGraphics::SetCullMode(CullMode cullMode)
{
}

void D3D11DynamicGraphics::EnableBlend()
{
}

void D3D11DynamicGraphics::EnableDepthTest()
{
}

void D3D11DynamicGraphics::DisableBlend()
{
}

void D3D11DynamicGraphics::DisableDepthTest()
{
}

void D3D11DynamicGraphics::ClearColorBuffer()
{
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, m_clearColor);
}

void D3D11DynamicGraphics::ClearColorDepthBuffer()
{
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, m_clearColor);
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

void D3D11DynamicGraphics::SwapBuffer()
{
    m_swapChain->Present(0, 0);
}

} /* namespace graphics */
} /* namespace tgon */