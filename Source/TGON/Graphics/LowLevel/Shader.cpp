#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"

#include "Shader.h"

namespace tgon
{

Shader::Shader(const char* vertexShaderCode, const char* fragmentShaderCode) :
    m_shaderImpl(vertexShaderCode, fragmentShaderCode)
{
}

void Shader::Use()
{
    m_shaderImpl.Use();
}

void Shader::Unuse()
{
    m_shaderImpl.Unuse();
}

void Shader::BindAttributeLocation(const char* name, uint32_t index)
{
    m_shaderImpl.BindAttributeLocation(name, index);
}

int Shader::GetUniformLocation(const char* name) const
{
    return m_shaderImpl.GetUniformLocation(name);
}

void Shader::SetParameter1f(const char* name, float f)
{
    this->SetParameter1f(this->GetUniformLocation(name), f);
}

void Shader::SetParameter2f(const char* name, float f1, float f2)
{
    this->SetParameter2f(this->GetUniformLocation(name), f1, f2);
}

void Shader::SetParameter3f(const char* name, float f1, float f2, float f3)
{
    this->SetParameter3f(this->GetUniformLocation(name), f1, f2, f3);
}

void Shader::SetParameter4f(const char* name, float f1, float f2, float f3, float f4)
{
    this->SetParameter4f(this->GetUniformLocation(name), f1, f2, f3, f4);
}

void Shader::SetParameterMatrix4fv(const char* name, const float* f)
{
    this->SetParameterMatrix4fv(this->GetUniformLocation(name), f);
}

void Shader::SetParameter1f(int32_t location, float f)
{
    m_shaderImpl.SetParameter1f(location, f);
}

void Shader::SetParameter2f(int32_t location, float f1, float f2)
{
    m_shaderImpl.SetParameter2f(location, f1, f2);
}

void Shader::SetParameter3f(int32_t location, float f1, float f2, float f3)
{
    m_shaderImpl.SetParameter3f(location, f1, f2, f3);
}

void Shader::SetParameter4f(int32_t location, float f1, float f2, float f3, float f4)
{
    m_shaderImpl.SetParameter4f(location, f1, f2, f3, f4);
}

void Shader::SetParameterMatrix4fv(int32_t location, const float* f)
{
    m_shaderImpl.SetParameterMatrix4fv(location, f);
}

void Shader::SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler)
{
    m_shaderImpl.SetParameterSampler(location, textureSlot, sampler);
}

bool Shader::IsValid() const noexcept
{
    return m_shaderImpl.IsValid();
}

} /* namespace tgon */
