#include "PrecompiledHeader.pch"
#include "Application.h"
#include "ApplicationType.h"

#include "Core/Platform/Window.h"

namespace tgon
{
namespace platform
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

const std::shared_ptr<Window>& Application::GetMainWindow() const noexcept
{
    return m_mainWindow;
}

} /* namespace platform */
} /* namespace tgon */