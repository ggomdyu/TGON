#include "PrecompiledHeader.h"

#include "GenericApplication.h"
#include "GenericApplicationType.h"

namespace tgon
{

GenericApplication::GenericApplication() :
    GenericApplication(nullptr)
{
}

GenericApplication::GenericApplication(const std::shared_ptr<GenericWindow>& rootWindow) :
    m_rootWindow(rootWindow)
{
}

void GenericApplication::ShowMessageBox(const char* message) const
{
    this->ShowMessageBox("", message);
}

void GenericApplication::ShowMessageBox(const char* message, MessageBoxIcon messageBoxIcon) const
{
    this->ShowMessageBox("", message, messageBoxIcon);
}

void GenericApplication::ShowMessageBox(const char* title, const char* message) const
{
    this->ShowMessageBox(title, message, MessageBoxIcon::Informational);
}

const std::shared_ptr<GenericWindow>& GenericApplication::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

void GenericApplication::AddModule(const std::shared_ptr<IModule>& module)
{
    m_modulesToFind.insert({ module->GetRTTI()->GetHashCode(), module });
    m_modules.push_back(module);
}

void GenericApplication::OnUpdate()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

} /* namespace tgon */