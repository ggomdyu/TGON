#include "PrecompiledHeader.h"

#include "Core/Object/Engine.h"

#include "Application.h"
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
    m_impl(new ApplicationImpl),
    m_engine(std::move(engine)),
    m_rootWindow(Window::Create(WindowStyle{}))
{
}

Application::~Application() = default;

void Application::MessageLoop()
{
    m_impl->MessageLoop([&]()
    {
        this->Update();
    });
}

void Application::Terminate()
{
    m_impl->Terminate();
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
    m_impl->ShowMessageBox(title, message, messageBoxIcon);
}
   
std::shared_ptr<Window> Application::GetRootWindow() noexcept
{
    return m_rootWindow;
}

std::shared_ptr<const Window> Application::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

const Engine* Application::GetEngine() const noexcept
{
    return m_engine.get();
}

Engine* Application::GetEngine() noexcept
{
    return m_engine.get();
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
