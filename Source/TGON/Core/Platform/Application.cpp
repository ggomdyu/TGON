#include "PrecompiledHeader.h"

#include "Core/Object/Engine.h"

#include "Application.h"
#include "ApplicationType.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplication.h"
#endif
#include "Window.h"
#include "WindowType.h"

namespace tgon
{

Application::Application(std::unique_ptr<Engine> engine) :
    m_engine(std::move(engine)),
    m_rootWindow(std::make_unique<Window>(WindowStyle{}))
{
}

Application::~Application() = default;

void Application::MessageLoop()
{
    m_applicationImpl->MessageLoop([&]()
    {
        this->Update();
    });
}

void Application::Terminate()
{
    m_applicationImpl->Terminate();
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
    m_applicationImpl->ShowMessageBox(title, message, messageBoxIcon);
}
   
Window& Application::GetRootWindow() noexcept
{
    return *m_rootWindow;
}

const Window& Application::GetRootWindow() const noexcept
{
    return *m_rootWindow;
}

const Engine& Application::GetEngine() const noexcept
{
    return *m_engine;
}

Engine& Application::GetEngine() noexcept
{
    return *m_engine;
}

const ApplicationImpl& Application::GetImpl() const noexcept
{
    return *m_applicationImpl;
}

ApplicationImpl& Application::GetImpl() noexcept
{
    return *m_applicationImpl;
}
    
void Application::Update()
{
    m_engine->Update();
}

void Application::OnDidLaunch()
{
    m_engine->OnDidLaunch();
}

void Application::OnWillTerminate()
{
    m_engine->OnWillTerminate();
}

} /* namespace tgon */
