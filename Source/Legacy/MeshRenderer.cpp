#include "PrecompiledHeader.h"

#include <algorithm>

#include "Graphics/ShaderProgram.h"
#include "Graphics/FVF.h"
#include "Graphics/OpenGL/OpenGLShaderCode.h"
#include "Graphics/Camera.h"

#include "MeshRenderer.h"

namespace tgon
{

void MeshRenderer::Update()
{
}

void MeshRenderer::Draw(Graphics& graphics)
{
}

void MeshRenderer::AddCamera(const std::shared_ptr<Camera>& camera)
{
    m_cameraList.push_back(camera);
}

bool MeshRenderer::RemoveCamera(const std::shared_ptr<Camera>& camera)
{
    auto iter = std::find_if(m_cameraList.begin(), m_cameraList.end(), [&](const std::shared_ptr<Camera>& comp)
    {
        return comp == camera;
    });

    if (iter != m_cameraList.end())
    {
        m_cameraList.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
