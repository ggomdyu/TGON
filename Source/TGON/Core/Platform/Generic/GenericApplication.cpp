#include "PrecompiledHeader.pch"

#include "GenericApplication.h"
#include "GenericApplicationType.h"

namespace tgon
{
namespace core
{

GenericApplication::GenericApplication(const std::shared_ptr<GenericWindow>& rootWindow) :
    m_rootWindow(rootWindow)
{
}

void GenericApplication::ShowMessageBox(const char* message) const
{
    this->ShowMessageBox("", message);
}

void GenericApplication::ShowMessageBox(const char* message, MessageBoxIconType messageBoxType) const
{
    this->ShowMessageBox("", message, messageBoxType);
}

void GenericApplication::ShowMessageBox(const char* title, const char* message) const
{
    this->ShowMessageBox(title, message, MessageBoxIconType::Informational);
}

const std::shared_ptr<GenericWindow>& GenericApplication::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

} /* namespace core */
} /* namespace tgon */
