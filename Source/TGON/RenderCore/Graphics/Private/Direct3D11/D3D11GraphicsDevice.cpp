#include "PrecompiledHeader.h"
#include "D3D11GraphicsDevice.h"

#include <Windows.h>

#define V(code)  m_lastError = code; if (m_lastError != S_OK) { return m_lastError; }

namespace tgon {
namespace graphics {

D3D11GraphicsDevice::D3D11GraphicsDevice(const TGraphicsDeviceProperty& graphicsProp, const platform::TSharedWindow& surfaceWindow) :
    GenericGraphicsDevice(surfaceWindow)
{
    this->Initialize(graphicsProp, surfaceWindow);
}

void D3D11GraphicsDevice::OnLostDevice()
{
}

void D3D11GraphicsDevice::OnResetDevice()
{
}


void CreateSwapChain(const TGraphicsDeviceProperty& graphicsDeviceProp)
{
	

}


HRESULT D3D11GraphicsDevice::Initialize(const TGraphicsDeviceProperty& graphicsDeviceProp, const platform::TSharedWindow& surfaceWindow)
{
	CComPtr<IDXGIFactory> giFactory;
    V(::CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&giFactory)));
    
    // Get Adapter to Graphics card
	CComPtr<IDXGIAdapter> giAdapter;
    V(giFactory->EnumAdapters(0, &giAdapter));

    // Enumerate Adapter to monitor
	CComPtr<IDXGIOutput> giOutput;
    V(giAdapter->EnumOutputs(0, &giOutput));

    // Get Count of display mode which support DXGI_FORMAT_R8G8B8A8_UNORM format
    uint32_t displayModeCount;
    V(giOutput->GetDisplayModeList(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModeCount, nullptr));

    std::vector<DXGI_MODE_DESC> displayModeDescRepository(displayModeCount);
    V(giOutput->GetDisplayModeList(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModeCount, displayModeDescRepository.data()));

	// Get the refresh rate of display mode
    for (const auto& displayModeDesc : displayModeDescRepository)
    {
        if (displayModeDesc.Width == graphicsDeviceProp.bufferWidth &&
            displayModeDesc.Height == graphicsDeviceProp.bufferHeight)
        {
            m_refreshRate = TRefreshRate(displayModeDesc.RefreshRate.Numerator, displayModeDesc.RefreshRate.Denominator);
        }
    }

	// Fill the information member
    DXGI_ADAPTER_DESC adapterDesc;
    giAdapter->GetDesc(&adapterDesc);
    {
        WideCharToMultiByte(CP_UTF8, 0, adapterDesc.Description, std::wcslen(adapterDesc.Description), &m_videoCardDescription[0], m_videoCardDescription.Capacity(), nullptr, nullptr);
        
        m_videoMemoryMiB = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
        m_vendorID = adapterDesc.VendorId;
    }

	/////////////////////////////////////////////
	// Create swap chain
	/////////////////////////////////////////////
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = graphicsDeviceProp.bufferWidth;
		swapChainDesc.BufferDesc.Height = graphicsDeviceProp.bufferHeight;
		swapChainDesc.BufferDesc.Format = static_cast<DXGI_FORMAT>(TFormat::R8G8B8A8_UNORM);

		// 백버퍼의 용도를 설정합니다.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		if (graphicsDeviceProp.enableVerticalSync)
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = m_refreshRate.numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = m_refreshRate.denominator;
		}
		else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		// 렌더링이 이루어질 윈도우의 핸들을 설정합니다.
		swapChainDesc.OutputWindow = surfaceWindow->GetWindowHandle();

		// Disable the multisampling
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = graphicsDeviceProp.fullscreen;

		// 스캔라인의 정렬과 스캔라이닝을 지정되지 않음으로(unspecified) 설정합니다. 
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;

		// 출력된 이후의 백버퍼의 내용을 버리도록 합니다. 
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// 추가 옵션 플래그를 사용하지 않습니다.
		swapChainDesc.Flags = 0;

		// 스왑 체인, Direct3D 디바이스, Direct3D 디바이스 컨텍스트를 생성합니다.
		do
		{
			D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
			m_lastError = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_giSwapChain, &m_d3dDevice, NULL, &m_d3dDeviceContext);
			if (m_lastError == S_OK)
			{
				break;
			}

			featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1;
			m_lastError = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_giSwapChain, &m_d3dDevice, NULL, &m_d3dDeviceContext);
			if (m_lastError == S_OK)
			{
				break;
			}

			featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_3;
			m_lastError = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_giSwapChain, &m_d3dDevice, NULL, &m_d3dDeviceContext);
			if (m_lastError != S_OK)
			{
				return false;
			}

		} while (0);
	}

	// 스왑체인이 생성되었으므로 백버퍼를 만들어주고, 그 포인터를 스왑체인에 연결시켜주는 과정.
	// 백버퍼의 포인터를 가져옵니다. -> 백버퍼를 만들지도 않았는데 백버퍼의 포인터를 가져온다니??
	{
		CComPtr<ID3D11Texture2D> backBuffer;
		V(m_giSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));

		// CreateRenderTargetView 함수를 사용하여 백버퍼를 스왑 체인에 연결합니다.
		V(m_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView));
	}

	{
		D3D11_TEXTURE2D_DESC depthBufferDesc {};
		depthBufferDesc.Width = graphicsDeviceProp.bufferWidth;
		depthBufferDesc.Height = graphicsDeviceProp.bufferHeight;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		// 깊이 버퍼 텍스처 생성
		V(m_d3dDevice->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer));

		// 깊이-스텐실 desc 작성
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc {};
		depthStencilDesc.DepthEnable = true; 
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; 
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS; 
		depthStencilDesc.StencilEnable = true; 
		depthStencilDesc.StencilReadMask = 0xFF; 
		depthStencilDesc.StencilWriteMask = 0xFF; 
		
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

		// 깊이-스텐실 상태를 생성합니다. 
		V(m_d3dDevice->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState));

		// 생성한 State를 적용한다. 이를 위해서 디바이스 컨텍스트를 사용.
		m_d3dDeviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		
		// 깊이-스텐실 뷰를 생성합니다.
		// 이 작업을 해야 Direct3D에서 깊이 버퍼를 깊이-스텐실 텍스처로 인식한다.
		V(m_d3dDevice->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView));

		// 렌더링 파이프에 렌더타겟 뷰와 깊이-스텐실 뷰를 바인딩함..
		// 이것을 통해 파이프라인을 통한 렌더링이 수행될때
		// 우리가 만든 백버퍼에 그려지게 된다.
		m_d3dDeviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	}

	// 래스터화기를 만들자.
	{
		D3D11_RASTERIZER_DESC rasterizerDesc {};
		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.MultisampleEnable = false;
		rasterizerDesc.ScissorEnable = true;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;

		V(m_d3dDevice->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState));

		m_d3dDeviceContext->RSSetState(m_rasterizerState);
	}

	// 뷰포트를 생성해야 렌더타겟 공간에서 클리핑 수행 가능.
	{
		D3D11_VIEWPORT viewport {};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = graphicsDeviceProp.bufferWidth;
		viewport.Height = graphicsDeviceProp.bufferHeight;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_d3dDeviceContext->RSSetViewports(1, &viewport);
	}

    return false;
}

HRESULT D3D11GraphicsDevice::GetLastError() const noexcept
{
    return m_lastError;
}

} /* namespace graphics */
} /* namespace tgon */