#include "PrecompiledHeader.pch"
#include "BaseApplication.h"

#include "Core/Platform/Window.h"

namespace tgon
{
namespace platform
{

BaseApplication::BaseApplication(const WindowStyle& windowStyle) :
    m_mainWindow(std::make_shared<Window>(windowStyle))
{
}

void BaseApplication::ShowMessageBox(const char* message) const
{
    this->ShowMessageBox("", message);
}

void BaseApplication::ShowMessageBox(const char* message, MessageBoxIconType messageBoxType) const
{
    this->ShowMessageBox("", message, messageBoxType);
}

const std::shared_ptr<BaseWindow>& BaseApplication::GetMainWindow() const
{
    return m_mainWindow;
}

} /* namespace platform */
} /* namespace tgon */
