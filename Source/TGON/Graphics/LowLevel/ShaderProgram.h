/**
 * @file    ShaderProgram.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLShaderProgram.h"
#endif

namespace tgon
{

class TGON_API ShaderProgram final :
    private PlatformShaderProgram
{
/**@section Method */
public:
    PlatformShaderProgram* GetPlatformDependency() noexcept;
    const PlatformShaderProgram* GetPlatformDependency() const noexcept;
    
    using PlatformShaderProgram::Use;
    using PlatformShaderProgram::Unuse;
    using PlatformShaderProgram::SetParameter1f;
    using PlatformShaderProgram::SetParameter2f;
    using PlatformShaderProgram::SetParameter3f;
    using PlatformShaderProgram::SetParameter4f;
    using PlatformShaderProgram::SetParameterMatrix4fv;
    using PlatformShaderProgram::SetParameterSampler;
    using PlatformShaderProgram::BindAttributeLocation;
    using PlatformShaderProgram::GetUniformLocation;
    using PlatformShaderProgram::IsValid;
};

} /* namespace tgon */
