#include "PrecompiledHeader.pch"
#include "BaseApplication.h"

namespace tgon
{
namespace platform
{

void BaseApplication::InitWithWindow(const std::shared_ptr<BaseWindow>& window)
{
    m_mainWindow = window;
}

const std::shared_ptr<BaseWindow>& BaseApplication::GetMainWindow() const
{
    return m_mainWindow;
}

} /* namespace platform */
} /* namespace tgon */
