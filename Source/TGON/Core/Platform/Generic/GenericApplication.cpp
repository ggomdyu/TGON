#include "PrecompiledHeader.pch"

#include "GenericApplication.h"
#include "GenericApplicationType.h"

namespace tgon
{
namespace core
{

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

const std::shared_ptr<class Window>& GenericApplication::GetMainWindow() const noexcept
{
    return m_mainWindow;
}

} /* namespace core */
} /* namespace tgon */
