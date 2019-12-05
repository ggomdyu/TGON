#include "PrecompiledHeader.h"

#include <algorithm>
#include <thread>

#include "Engine.h"

namespace tgon
{

Engine::~Engine() = default;

void Engine::Initialize()
{
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
