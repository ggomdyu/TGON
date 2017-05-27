/**
 * @filename    D3D9GraphicsDevice.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#define TGON_GRAPHICS_DIRECT3D11

#include "../Generic/GenericGraphicsDevice.h"
//#include "Core/Platform/Windows/Misc/UniqueComPtr.h"

#include <vector>
#include <atlbase.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace tgon {
namespace graphics {

class TGON_API D3D11GraphicsDevice :
    public GenericGraphicsDevice
{
/**
 * @section Ctor/Dtor
 */
public:
    D3D11GraphicsDevice(const TGraphicsDeviceProperty& graphicsProp, const platform::TSharedWindow& surfaceWindow);
    virtual ~D3D11GraphicsDevice() = default;

/**
 * @section Event handler
 */
public:
    void OnLostDevice();
    void OnResetDevice();
    void OnWindowResized();

private:
    HRESULT Initialize(const TGraphicsDeviceProperty& graphicsProp, const platform::TSharedWindow& surfaceWindow);

/**
 * @section Get method
 */
public:
    HRESULT GetLastError() const noexcept;
    //IDirect3DDevice9Ex* GetRawDevice();

/**
 * @section Private member variable
 */
private:
	CComPtr<IDXGISwapChain> m_giSwapChain;
	CComPtr<ID3D11Device> m_d3dDevice;
	CComPtr<ID3D11DeviceContext> m_d3dDeviceContext;
	CComPtr<ID3D11RenderTargetView> m_renderTargetView;
	CComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	CComPtr<ID3D11DepthStencilState> m_depthStencilState;
	CComPtr<ID3D11DepthStencilView> m_depthStencilView;
	CComPtr<ID3D11RasterizerState> m_rasterizerState;

    HRESULT m_lastError;
};

using TGraphicsDevice = D3D11GraphicsDevice;

} /* namespace graphics */
} /* namespace tgon */