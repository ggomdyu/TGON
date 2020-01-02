#include "PrecompiledHeader.h"

#include "Application.h"

namespace tgon
{
    
extern std::unique_ptr<Engine> CreateEngine();

Application::Application() :
    m_engine(CreateEngine()),
    m_rootWindow(std::make_unique<Window>(WindowStyle{}))
{
}

Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

void Application::ShowMessageBox(const char* message)
{
    ShowMessageBox("", message);
}

void Application::ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon)
{
    ShowMessageBox("", message, messageBoxIcon);
}

void Application::ShowMessageBox(const char* title, const char* message)
{
    ShowMessageBox(title, message, MessageBoxIcon::Informational);
}

std::shared_ptr<Engine> Application::GetEngine() noexcept
{
    return GetInstance().m_engine;
}

std::shared_ptr<Window> Application::GetRootWindow() noexcept
{
    return GetInstance().m_rootWindow;
}

PlatformApplication& Application::GetPlatformDependency() noexcept
{
    return *this;
}
    
const PlatformApplication& Application::GetPlatformDependency() const noexcept
{
    return *this;
}
    
void Application::OnLaunch()
{
    m_engine->Initialize();
}

void Application::OnTerminate()
{
    m_engine->Destroy();
}

} /* namespace tgon */
