#include "PrecompiledHeader.h"

#include "Core/Random/Random.h"

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

void GenericApplication::ShowMessageBox(const char* message, MessageBoxIcon messageBoxType) const
{
    this->ShowMessageBox("", message, messageBoxType);
}

void GenericApplication::ShowMessageBox(const char* title, const char* message) const
{
    this->ShowMessageBox(title, message, MessageBoxIcon::Informational);
}

const std::shared_ptr<GenericWindow>& GenericApplication::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

void GenericApplication::OnUpdate()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
}

void GenericApplication::AddModule(const std::shared_ptr<IModule>& module)
{
    m_modules.push_back(module);
}

void GenericApplication::AddModule(std::initializer_list<const std::shared_ptr<IModule>&> modules)
{
    m_modules.reserve(modules.size());

    for (auto& module : m_modules)
    {
        m_modules.push_back(module);
    }
}

} /* namespace tgon */