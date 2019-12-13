/**
 * @file    Material.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "ShaderProgram.h"
#include "Pass.h"

namespace tgon
{

class Material :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit Material(ShaderProgram&& shaderProgram) noexcept;
    Material(const char* vertexShaderCode, const char* fragmentShaderCode);

/**@section Destructor */
public:
    ~Material() = default;

/**@section Method */
public:
    void Use();
    void Unuse();
    ShaderProgram& GetShaderProgram() noexcept;
    const ShaderProgram& GetShaderProgram() const noexcept;
    
/**@section Variable */
protected:
    ShaderProgram m_shaderProgram;
};

} /* namespace tgon */
