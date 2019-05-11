/**
 * @file    Material.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Core/CoreObject.h"
#include "Math/Color.h"
#include "Math/Matrix4x4.h"

#include "Texture.h"
#include "ShaderProgram.h"
#include "GraphicsType.h"

namespace tgon
{

class TGON_API Material :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Material);
    
/**@section Constructor */
public:
    Material(const char* vertexShaderCode, const char* fragmentShaderCode);

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
//    std::unordered_map<int32_t, std::shared_ptr<Texture>> m_textures;
    ShaderProgram m_shaderProgram;
};

} /* namespace tgon */
