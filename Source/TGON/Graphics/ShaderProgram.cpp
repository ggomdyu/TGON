#include "PrecompiledHeader.h"

#include "ShaderProgram.h"

namespace tgon
{

PlatformShaderProgram* ShaderProgram::GetPlatformDependency() noexcept
{
    return this;
}
    
const PlatformShaderProgram* ShaderProgram::GetPlatformDependency() const noexcept
{
    return this;
}

}
