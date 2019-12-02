#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    if (m_nextScene != nullptr)
    {
        m_currScene = std::move(m_nextScene);
        m_currScene->Initialize();
    }
    
    m_currScene->Update();
}

} /* namespace tgon */
