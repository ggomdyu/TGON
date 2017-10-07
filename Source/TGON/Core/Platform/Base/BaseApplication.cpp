#include "PrecompiledHeader.pch"
#include "BaseApplication.h"

namespace tgon
{
namespace platform
{

BaseApplication::BaseApplication(const std::shared_ptr<class BaseWindow>& mainWindow) :
    m_mainWindow(mainWindow)
{
}

const std::shared_ptr<BaseWindow>& BaseApplication::GetMainWindow() const
{
    return m_mainWindow;
}

} /* namespace platform */
} /* namespace tgon */
