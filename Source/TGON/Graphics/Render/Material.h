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
#include "Graphics/LowLevel/Shader.h"
#include "Graphics/LowLevel/GraphicsType.h"

namespace tgon
{

class TGON_API Material :
    public RuntimeObject
{
public:
    TGON_RUNTIME_OBJECT(Material);
    
/* @section Public constructor */
public:
    explicit Material(const std::shared_ptr<Shader>& shader);

/* @section Public destructor */
public:
    virtual ~Material() = default;

/* @section Public method */
public:
    virtual void Use() = 0;
    
    virtual void Unuse() = 0;
    
    /* @brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const = 0;
    
    /* @brief   Sets the world-view-projection matrix. */
    void SetWVP(const Matrix4x4& matWVP);
    
    /* @brief   Gets the world-view-projection matrix. */
    Matrix4x4& GetWVP() noexcept;
    
    /* @brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetWVP() const noexcept;
    
    FillMode GetFillMode() const noexcept;
    
    CullMode GetCullMode();
    
    /* @brief   Gets the shader. */
    std::shared_ptr<Shader>& GetShader() noexcept;
    
    /* @brief   Gets the shader. */
    const std::shared_ptr<Shader>& GetShader() const noexcept;
    
/* @section Protected variable */
protected:
    Matrix4x4 m_matWVP;
    
    CullMode m_cullMode;
    
    FillMode m_fillMode;
    
    std::shared_ptr<Shader> m_shader;
};

class TGON_API ColorMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(ColorMaterial);

/* @section Public constructor */
public:
    ColorMaterial();

/* @section Public destructor */
public:
    virtual ~ColorMaterial() override = default;

/* @section Public method */
public:
    virtual void Use() override;
    
    virtual void Unuse() override;
    
    virtual bool CanBatch(const Material& rhs) const override;
    
    void SetColor(const Color4f& color);
    
    const Color4f& GetColor() const noexcept;

/* @section Private variable */
private:
    Color4f m_color;
};

class TGON_API TextureMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(TextureMaterial);

/* @section Public constructor */
public:
    TextureMaterial();
    
    TextureMaterial(const std::shared_ptr<Texture>& texture, const Color4f& blendColor);
    
    explicit TextureMaterial(const std::shared_ptr<Texture>& texture);

/* @section Public destructor */
public:
    virtual ~TextureMaterial() override = default;

/* @section Public method */
public:
    virtual void Use() override;
    
    virtual void Unuse() override;
    
    /* @brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const override;
    
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    
    void SetBlendColor(const Color4f& blendColor) noexcept;
    
    std::shared_ptr<Texture>& GetTexture() noexcept;
    
    const std::shared_ptr<Texture>& GetTexture() const noexcept;
    
    Color4f& GetBlendColor() noexcept;
    
    const Color4f& GetBlendColor() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
    
    Color4f m_blendColor;
};

//class GrayscaleTextureMaterial :
//    public TextureMaterial
//{
//public:
//    TGON_RUNTIME_OBJECT(GrayscaleTextureMaterial);
//
///* @section Public constructor */
//public:
//    GrayscaleTextureMaterial();
//
//    /* @section Public destructor */
//public:
//    virtual ~GrayscaleTextureMaterial() override = default;
//
//    /* @section Public method */
//public:
//    virtual void Use() override;
//    virtual void Unuse() override;
//    virtual bool CanBatch(const Material& rhs) const override;
//};

class MaskTextureMaterial :
    public TextureMaterial
{
public:
    TGON_RUNTIME_OBJECT(MaskTextureMaterial);

/* @section Public constructor */
public:
    MaskTextureMaterial() = default;

/* @section Public destructor */
public:
    virtual ~MaskTextureMaterial() override = default;

/* @section Public method */
public:
    virtual void Use() override;
    
    virtual void Unuse() override;
    
    virtual bool CanBatch(const Material& rhs) const override;
    
    void SetMaskTexture(const std::shared_ptr<Texture>& maskTexture);
    
    std::shared_ptr<Texture>& GetMaskTexture() noexcept;
    
    const std::shared_ptr<Texture>& GetMaskTexture() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Texture> m_maskTexture;
};

//class GrayTextureMaterial :
//    public TextureMaterial
//{
//public:
//    TGON_RUNTIME_OBJECT(GrayTextureMaterial);
//};
//
class UberMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(UberMaterial);
};

} /* namespace tgon */
