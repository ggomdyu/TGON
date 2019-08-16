#include "PrecompiledHeader.h"

#include "Random/WELL1024a.h"

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

Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

void Application::ShowMessageBox(const std::string_view& message)
{
    ShowMessageBox("", message);
}

void Application::ShowMessageBox(const std::string_view& message, MessageBoxIcon messageBoxIcon)
{
    ShowMessageBox("", message, messageBoxIcon);
}

void Application::ShowMessageBox(const std::string_view& title, const std::string_view& message)
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
    auto engine = GetEngine();
    if (engine)
    {
        engine->OnLaunch();
    }
}

void Application::OnTerminate()
{
    auto engine = GetEngine();
    if (engine)
    {
        engine->OnTerminate();
    }
}

} /* namespace tgon */
