#include "PrecompiledHeader.pch"
#include "GameApplication.h"

namespace tgon
{

GameApplication::GameApplication(const std::shared_ptr<platform::Window>& window) :
	m_paused(false),
	m_rootWindow(window)
{
}

void GameApplication::ResumeUpdate() noexcept
{
    m_paused = false;
}

void tgon::GameApplication::PauseUpdate() noexcept
{
    m_paused = true;
}

const std::shared_ptr<platform::Window>& GameApplication::GetRootWindow() const noexcept
{
    return m_rootWindow;
}

bool tgon::GameApplication::IsPaused() const noexcept
{
    return m_paused;
}

} /* namespace tgon */
