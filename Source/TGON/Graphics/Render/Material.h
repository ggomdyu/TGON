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
    
/**@section Protected constructor */
protected:
    explicit Material(const std::shared_ptr<ShaderProgram>& shader);

/**@section Public destructor */
public:
    virtual ~Material() = default;

/**@section Public method */
public:
    virtual void Use() = 0;
    virtual void Unuse() = 0;
    
    /**@brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const = 0;
    
    /**@brief   Sets the world-view-projection matrix. */
    void SetWVP(const Matrix4x4& matWVP);
    
    /**@brief   Gets a shader managed by this material. */
    std::shared_ptr<ShaderProgram>& GetShader() noexcept;
    
    /**@brief   Gets a shader managed by this material. */
    const std::shared_ptr<ShaderProgram>& GetShader() const noexcept;
    
/**@section Protected variable */
protected:
    std::shared_ptr<ShaderProgram> m_shader;
};

} /* namespace tgon */
