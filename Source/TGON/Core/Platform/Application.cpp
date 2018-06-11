#include "PrecompiledHeader.h"

#include "Core/Object/Engine.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsApplication.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSApplication.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidApplication.h"
#elif TGON_PLATFORM_IOS
#   import "IOS/IOSApplication.h"
#endif

#include "Application.h"
#include "Window.h"
#include "WindowType.h"

namespace tgon
{
    
extern std::shared_ptr<Engine> MakeEngine();

Application::Application() :
    m_impl(std::make_shared<ApplicationImpl>()),
    m_engine(MakeEngine()),
    m_rootWindow(m_engine->GetRootWindowStyle())
{
}
    
Application::Application(const WindowStyle& windowStyle) :
    m_impl(std::make_shared<ApplicationImpl>()),
    m_engine(MakeEngine()),
    m_rootWindow(windowStyle)
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
    
void Application::SetRootWindow(Window&& window) noexcept
{
//    m_rootWindow = std::move(window);
}
    
Window& Application::GetRootWindow() noexcept
{
    return m_rootWindow;
}

const Window& Application::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

void Application::SetEngine(const std::shared_ptr<Engine>& engine) noexcept
{
    m_engine = engine;
}

std::weak_ptr<Engine> Application::GetEngine() noexcept
{
    return m_engine;
}

std::weak_ptr<const Engine> Application::GetEngine() const noexcept
{
    return m_engine;
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
