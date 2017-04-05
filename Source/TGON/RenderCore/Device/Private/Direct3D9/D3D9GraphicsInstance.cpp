#include "PrecompiledHeader.h"
#include "D3D9GraphicsInstance.h"

namespace tgon
{

D3D9GraphicsInstance::D3D9GraphicsInstance()
{
    HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_d3d);
    if (FAILED(hr))
    {
        m_state = EGraphicsInstanceState::FailedToCreate;
        return;
    }
}

D3D9GraphicsInstance::~D3D9GraphicsInstance()
{
}

UniqueComPtr<IDirect3D9Ex>& D3D9GraphicsInstance::GetD3D()
{
    return m_d3d;
}

} /* namespace tgon */