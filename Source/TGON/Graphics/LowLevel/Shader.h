/**
 * @file    Shader.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLShader.h"
#endif

namespace tgon
{

class TGON_API Shader final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Shader(const char* vertexShaderCode, const char* fragmentShaderCode);
    
/* @section Public method */
public:
    void Use();
    void Unuse();
    
    void SetParameter1f(const char* name, float f);
    void SetParameter2f(const char* name, float f1, float f2);
    void SetParameter3f(const char* name, float f1, float f2, float f3);
    void SetParameter4f(const char* name, float f1, float f2, float f3, float f4);
    void SetParameterMatrix4fv(const char* name, const float* f);
    void SetParameter1f(int32_t location, float f);
    void SetParameter2f(int32_t location, float f1, float f2);
    void SetParameter3f(int32_t location, float f1, float f2, float f3);
    void SetParameter4f(int32_t location, float f1, float f2, float f3, float f4);
    void SetParameterMatrix4fv(int32_t location, const float* f);
    void SetParameterSampler(int32_t location, uint32_t textureSlot, uint32_t sampler);
    
    void BindAttributeLocation(const char* name, uint32_t location);
    int GetUniformLocation(const char* name) const;
    
    /* @brief   Checks the shader was loaded successfully. */
    bool IsValid() const noexcept;
    
/* @section Private variable */
public:
    ShaderImpl m_shaderImpl;
};

} /* namespace tgon */
