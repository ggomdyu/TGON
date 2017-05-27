#include "PrecompiledHeader.h"
#include "D3DX11Renderer.h"

namespace tgon
{

D3D9Renderer::~D3D9Renderer()
{
}

void D3D9Renderer::Clear()
{
    m_d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_clearColor, 1.0f, 0.0f);
}

void D3D9Renderer::BeginScene()
{
    m_d3dDevice->BeginScene();
}

void D3D9Renderer::EndScene()
{
    m_d3dDevice->EndScene();
}

void D3D9Renderer::Present()
{
    m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D9Renderer::OnLostDevice()
{
}

void D3D9Renderer::OnResetDevice()
{
}

} /* namespace tgon */