#include "PrecompiledHeader.pch"

#include "Application.h"

namespace tgon
{
namespace core
{
namespace
{

Application* g_application;

} /* namespace */

Application::Application() :
    SuperType()
{
    g_application = this;
}

Application::Application(const WindowStyle& windowStyle) :
    SuperType(windowStyle)
{
    g_application = this;
}

Application* Application::GetInstance()
{
    return g_application;
}

} /* namespace core */
} /* namespace tgon */
