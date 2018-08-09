#include "PrecompiledHeader.h"

#include "Core/Engine/Engine.h"
#include "Core/Random/WELL1024a.h"

#include "Application.h"

namespace tgon
{

Application::Application() :
    m_rootWindow(std::make_unique<Window>(WindowStyle{}))
{
    SrandWELL1024a();
}
    
Application* Application::GetInstance()
{
    static Application instance;
    return &instance;
}

void Application::Terminate()
{
    m_applicationImpl.Terminate();
}

void Application::ShowMessageBox(const char* message) const
{
    this->ShowMessageBox("", message);
}

void Application::ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const
{
    this->ShowMessageBox("", message, messageBoxIcon);
}

void Application::ShowMessageBox(const char* title, const char* message) const
{
    this->ShowMessageBox(title, message, MessageBoxIcon::Informational);
}

void Application::ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const
{
    m_applicationImpl.ShowMessageBox(title, message, messageBoxIcon);
}
   
Window& Application::GetRootWindow() noexcept
{
    return *m_rootWindow;
}

const Window& Application::GetRootWindow() const noexcept
{
    return *m_rootWindow;
}

} /* namespace tgon */
