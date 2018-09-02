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
    PlatformApplication::MessageLoop([&]()
    {
        m_engine->Update();
    });
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

Engine* Application::GetEngine()
{
    return m_engine.get();
}

const Engine* Application::GetEngine() const
{
    return m_engine.get();
}

Window& Application::GetRootWindow() noexcept
{
    return *m_rootWindow;
}

const Window& Application::GetRootWindow() const noexcept
{
    return *m_rootWindow;
}

void Application::OnDidLaunch()
{
    if (m_engine)
    {
        m_engine->OnDidLaunch();
    }
}

void Application::OnWillTerminate()
{
    if (m_engine)
    {
        m_engine->OnWillTerminate();
    }
}

} /* namespace tgon */
