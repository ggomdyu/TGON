/**
 * @file    Material.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Core/Object/CoreObject.h"
#include "Core/Math/Color.h"
#include "Core/Math/Matrix4x4.h"
#include "Graphics/LowLevel/Texture.h"
#include "Graphics/LowLevel/ShaderProgram.h"
#include "Graphics/LowLevel/GraphicsType.h"

namespace tgon
{

class TGON_API Material :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Material);
    
/**@section Constructor */
protected:
    explicit Material(const std::shared_ptr<ShaderProgram>& shader);

/**@section Destructor */
public:
    virtual ~Material() = default;

/**@section Method */
public:
    void Use();
    void Unuse();
    
    /**@brief   Gets a shader managed by this material. */
    std::shared_ptr<ShaderProgram> GetShaderProgram() noexcept;
    
    /**@brief   Gets a shader managed by this material. */
    std::shared_ptr<const ShaderProgram> GetShaderProgram() const noexcept;
    
/**@section Variable */
protected:
    std::unordered_map<int32_t, std::shared_ptr<Texture>> m_textures;

    std::shared_ptr<ShaderProgram> m_shader;
};

} /* namespace tgon */
