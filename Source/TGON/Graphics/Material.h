/**
 * @file    Material.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Core/NonCopyable.h"

#include "ShaderProgram.h"

namespace tgon
{

class TGON_API Material :
    private NonCopyable
{
/**@section Constructor */
public:
    Material(const char* vertexShaderCode, const char* fragmentShaderCode);
    explicit Material(ShaderProgram&& shaderProgram) noexcept;

/**@section Destructor */
public:
    virtual ~Material() = default;

/**@section Method */
public:
    void Use();
    void Unuse();
    
    /**@brief   Gets a shader managed by this material. */
    ShaderProgram& GetShaderProgram() noexcept;
    
    /**@brief   Gets a shader managed by this material. */
    const ShaderProgram& GetShaderProgram() const noexcept;
    
/**@section Variable */
protected:
    ShaderProgram m_shaderProgram;
};

} /* namespace tgon */
