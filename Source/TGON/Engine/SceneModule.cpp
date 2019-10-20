#include "PrecompiledHeader.h"

#include "SceneModule.h"

namespace tgon
{

void SceneModule::Update()
{
    m_currScene->Update();
}

} /* namespace tgon */
