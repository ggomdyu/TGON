#include "PrecompiledHeader.h"

#include <sstream>

#include "WindowsInputManager.h"

namespace tgon
{

WindowsInputManager::WindowsInputManager() :
    m_nativeInputManager(nullptr)
{
}

WindowsInputManager::WindowsInputManager(const Window& window)
{
    this->Initialize(window);
}

WindowsInputManager::~WindowsInputManager()
{
}

void WindowsInputManager::Initialize(const Window& window)
{
    m_nativeInputManager = OIS::InputManager::createInputSystem(QueryParamList(window));
}

OIS::ParamList WindowsInputManager::QueryParamList(const Window& window)
{
    std::ostringstream os;
    os << reinterpret_cast<std::size_t>(window.GetNativeWindow());

    return {{"WINDOW", os.str()}};
}

} /* namespace tgon */