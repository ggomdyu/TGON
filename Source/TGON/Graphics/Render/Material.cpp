#include "PrecompiledHeader.h"

#if TGON_USING_OPENGL
#   include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#endif

#include "Material.h"

namespace tgon
{

Material::Material(const std::shared_ptr<ShaderProgram>& shader) :
    m_shader(shader)
{
}

void Material::SetWVP(const Matrix4x4& matWVP)
{
    m_shader->SetParameterMatrix4fv("g_uWVP", matWVP[0]);
}

std::shared_ptr<ShaderProgram> Material::GetShaderProgram() noexcept
{
    return m_shader;
}

std::shared_ptr<const ShaderProgram> Material::GetShaderProgram() const noexcept
{
    return m_shader;
}

} /* namespace tgon */
