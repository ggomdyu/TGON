#include "PrecompiledHeader.h"

#if TGON_USING_OPENGL
#   include "Graphics/OpenGL/OpenGLShaderCode.h"
#endif

#include "Material.h"

namespace tgon
{

Material::Material(const char* vertexShaderCode, const char* fragmentShaderCode) :
    m_shaderProgram(vertexShaderCode, fragmentShaderCode)
{
}
    
void Material::Use()
{
    m_shaderProgram.Use();
}

void Material::Unuse()
{
    m_shaderProgram.Unuse();
}
    
ShaderProgram& Material::GetShaderProgram() noexcept
{
    return m_shaderProgram;
}

const ShaderProgram& Material::GetShaderProgram() const noexcept
{
    return m_shaderProgram;
}

} /* namespace tgon */
