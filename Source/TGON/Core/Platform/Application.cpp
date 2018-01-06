#include "PrecompiledHeader.pch"

#include "Application.h"
#include "ApplicationType.h"

namespace tgon
{
namespace core
{

void Application::ShowMessageBox(const char* message) const
{
    this->ShowMessageBox("", message);
}

void Application::ShowMessageBox(const char* message, MessageBoxIconType messageBoxType) const
{
    this->ShowMessageBox("", message, messageBoxType);
}

void Application::ShowMessageBox(const char* title, const char* message) const
{
    this->ShowMessageBox(title, message, MessageBoxIconType::Informational);
}

const std::shared_ptr<class Window>& Application::GetMainWindow() const noexcept
{
    return m_mainWindow;
}

} /* namespace core */
} /* namespace tgon */
