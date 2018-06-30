#include "PrecompiledHeader.h"

#include "Mouse.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif
#include "InputManager.h"

namespace tgon
{
    
Mouse::Mouse(InputManager& inputManager) :
    m_mouseImpl(std::make_unique<MouseImpl>(inputManager.GetImpl()))
{
}
    
Mouse::~Mouse() = default;
    
void Mouse::Update()
{
    m_mouseImpl->Update();
}

void Mouse::GetPosition(int32_t* x, int32_t* y)
{
    MouseImpl::GetPosition(x, y);
}

I32Point Mouse::GetPosition()
{
    I32Point pt;
    MouseImpl::GetPosition(&pt.x, &pt.y);

    return pt;
}
    
bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    return m_mouseImpl->IsMouseDown(mouseCode);
}

bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    return m_mouseImpl->IsMouseHold(mouseCode);
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    return m_mouseImpl->IsMouseUp(mouseCode);
}

const MouseImpl& Mouse::GetImpl() const noexcept
{
    return *m_mouseImpl;
}

MouseImpl& Mouse::GetImpl() noexcept
{
    return *m_mouseImpl;
}

} /* namespace tgon */
