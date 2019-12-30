#include "PrecompiledHeader.h"

#include <algorithm>
#include <thread>

#include "Engine.h"

namespace tgon
{

Engine::~Engine()
{
    m_moduleDict.clear();

    while (m_modules.empty() == false)
    {
        m_modules.pop_back();
    }
}

void Engine::Update()
{
    for (auto& module : m_modules)
    {
        module->Update();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} /* namespace tgon */
