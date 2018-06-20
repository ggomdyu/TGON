#include "PrecompiledHeader.h"

#include "Core/Object/Engine.h"

#include "Application.h"
#include "Window.h"
#include "WindowType.h"

namespace tgon
{

Application::Application(std::unique_ptr<Engine> engine) :
    m_engine(std::move(engine)),
    m_rootWindow(Window::Create(WindowStyle{}))
{
}

Application::~Application() = default;

void Application::MessageLoop()
{
    m_platformApplication.MessageLoop([&]()
    {
        this->Update();
    });
}

void Application::Terminate()
{
    m_platformApplication.Terminate();
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
    m_platformApplication.ShowMessageBox(title, message, messageBoxIcon);
}
   
std::shared_ptr<Window> Application::GetRootWindow() noexcept
{
    return m_rootWindow;
}

std::shared_ptr<const Window> Application::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

const Engine& Application::GetEngine() const noexcept
{
    return *m_engine;
}

Engine& Application::GetEngine() noexcept
{
    return *m_engine;
}

const PlatformApplication& Application::GetPlatformDependency() const noexcept
{
    return m_platformApplication;
}

PlatformApplication& Application::GetPlatformDependency() noexcept
{
    return m_platformApplication;
}

void Application::OnDidLaunch()
{
    m_engine->OnDidLaunch();
}
    
void Application::OnWillTerminate()
{
    m_engine->OnWillTerminate();
}
    
void Application::Update()
{
    m_engine->Update();
}

} /* namespace tgon */
