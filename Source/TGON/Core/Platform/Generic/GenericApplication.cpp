#include "PrecompiledHeader.pch"

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

} /* namespace tgon */