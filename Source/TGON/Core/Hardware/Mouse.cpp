#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif

#include "Mouse.h"
#include "InputManager.h"

namespace tgon
{
    
Mouse::Mouse(InputManager* inputManager) :
    m_impl(std::make_shared<MouseImpl>(inputManager->GetImpl()))
{
}
    
void Mouse::Update()
{
    m_impl->Update();
}
    
bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    return m_impl->IsMouseDown(mouseCode);
}

bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    return m_impl->IsMouseHold(mouseCode);
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    return m_impl->IsMouseUp(mouseCode);
}

const MouseImpl* Mouse::GetImpl() const noexcept
{
    return m_impl.get();
}

MouseImpl* Mouse::GetImpl() noexcept
{
    return m_impl.get();
}

} /* namespace tgon */