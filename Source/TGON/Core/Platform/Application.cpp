#include "PrecompiledHeader.h"

#include "Application.h"

namespace tgon
{

void Application::MessageLoop()
{
    m_impl.MessageLoop([&]()
    {
        this->OnUpdate();
    });
}

void Application::Terminate()
{
    m_impl.Terminate();
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
    m_impl.ShowMessageBox(title, message, messageBoxIcon);
}

Window& Application::GetRootWindow() noexcept
{
    return m_rootWindow;
}

const Window& Application::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

void Application::AddModule(const std::shared_ptr<IModule>& module)
{
    m_modulesToFind.insert({ module->GetRTTI()->GetHashCode(), module });
    m_modules.push_back(module);
}

void Application::OnUpdate()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

} /* namespace tgon */