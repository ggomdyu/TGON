#include "PrecompiledHeader.h"

#include "Core/Random/WELL1024a.h"

#include "Application.h"

namespace tgon
{
    
extern std::unique_ptr<Engine> CreateEngine();

Application::Application() :
    m_engine(CreateEngine()),
    m_rootWindow(std::make_unique<Window>(WindowStyle{}))
{
    SrandWELL1024a();
}
    
Application* Application::GetInstance()
{
    static Application instance;
    return &instance;
}

void Application::MessageLoop()
{
    PlatformApplication::MessageLoop([&](){ m_engine->Update(); });
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

std::shared_ptr<Engine> Application::GetEngine() noexcept
{
    return m_engine;
}
    
std::shared_ptr<const Engine> Application::GetEngine() const noexcept
{
    return m_engine;
}

std::shared_ptr<Window> Application::GetRootWindow() noexcept
{
    return m_rootWindow;
}
    
std::shared_ptr<const Window> Application::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

PlatformApplication* Application::GetPlatformDependency() noexcept
{
    return this;
}
    
const PlatformApplication* Application::GetPlatformDependency() const noexcept
{
    return this;
}
    
void Application::OnLaunch()
{
    if (m_engine)
    {
        m_engine->OnLaunch();
    }
}

void Application::OnTerminate()
{
    if (m_engine)
    {
        m_engine->OnTerminate();
    }
}

} /* namespace tgon */
