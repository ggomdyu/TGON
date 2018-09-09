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
    
/* @section Protected constructor */
protected:
    explicit Material(const std::shared_ptr<Shader>& shader) :
        m_shader(shader)
    {
    }

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
    void SetWVP(const Matrix4x4& matWVP)
    {
        m_shader->SetParameterMatrix4fv("g_uWVP", matWVP[0]);
    }
    
    /* @brief   Gets the shader. */
    std::shared_ptr<Shader>& GetShader() noexcept
    {
        return m_shader;
    }
    
    /* @brief   Gets the shader. */
    const std::shared_ptr<Shader>& GetShader() const noexcept
    {
        return m_shader;
    }
    
/* @section Protected variable */
protected:
    std::shared_ptr<Shader> m_shader;
};

class TGON_API ColorMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(ColorMaterial);

/* @section Public constructor */
public:
    ColorMaterial(const Color4f& blendColor);

    ColorMaterial() :
        ColorMaterial(Color4f(1.0f, 1.0f, 1.0f, 1.0f))
    {
    }

/* @section Protected constructor */
protected:
    ColorMaterial(const std::shared_ptr<Shader>& shader, const Color4f& blendColor) :
        Material(shader),
        m_blendColor(blendColor)
    {
    }
    
/* @section Public destructor */
public:
    virtual ~ColorMaterial() override = default;

/* @section Public method */
public:
    virtual void Use() override
    {
        m_shader->Use();
        m_shader->SetParameter4f("g_uColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, m_blendColor.a);
    }
    
    virtual void Unuse() override
    {
        m_shader->Unuse();
    }
    
    virtual bool CanBatch(const Material& rhs) const override;
    
    void SetBlendColor(const Color4f& blendColor)
    {
        m_blendColor = blendColor;
    }

    Color4f& GetBlendColor() noexcept
    {
        return m_blendColor;
    }

    const Color4f& GetBlendColor() const noexcept
    {
        return m_blendColor;
    }

/* @section Protected variable */
protected: 
    Color4f m_blendColor;
};
    
class TGON_API TextureMaterial :
    public ColorMaterial
{
public:
    TGON_RUNTIME_OBJECT(TextureMaterial);

/* @section Public constructor */
public:
    TextureMaterial(const std::shared_ptr<Texture>& texture, const Color4f& blendColor);
    
    TextureMaterial() :
        TextureMaterial(nullptr)
    {
    }

    TextureMaterial(const std::shared_ptr<Texture>& texture) :
        TextureMaterial(texture, Color4f(1.0f, 1.0f, 1.0f, 1.0f))
    {
    }

/* @section Protected constructor */
protected:
    TextureMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const Color4f& blendColor) :
        ColorMaterial(shader, blendColor),
        m_texture(texture)
    {
    }

/* @section Public destructor */
public:
    virtual ~TextureMaterial() override = default;

/* @section Public method */
public:
    virtual void Use() override
    {
        m_shader->Use();
        m_shader->SetParameter4f("g_uBlendColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, m_blendColor.a);

        m_texture->Use();
    }
    
    virtual void Unuse() override
    {
    }
    
    /* @brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const override;
    
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept
    {
        m_texture = texture;
    }
    
    const std::shared_ptr<Texture>& GetTexture() noexcept
    {
        return m_texture;
    }
    
    std::shared_ptr<const Texture> GetTexture() const noexcept
    {
        return m_texture;
    }
    
/* @section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
};

class TGON_API AlphaTextureMaterial :
    public ColorMaterial
{
public:
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
//
//class MaskTextureMaterial :
//    public TextureMaterial
//{
//public:
//    TGON_RUNTIME_OBJECT(MaskTextureMaterial);
//
///* @section Public constructor */
//public:
//    MaskTextureMaterial() = default;
//
///* @section Public destructor */
//public:
//    virtual ~MaskTextureMaterial() override = default;
//
///* @section Public method */
//public:
//    virtual void Use() override;
//    
//    virtual void Unuse() override;
//    
//    virtual bool CanBatch(const Material& rhs) const override;
//    
//    void SetMaskTexture(const std::shared_ptr<Texture>& maskTexture);
//    
//    std::shared_ptr<Texture>& GetMaskTexture() noexcept;
//    
//    const std::shared_ptr<Texture>& GetMaskTexture() const noexcept;

//
//void MaskTextureMaterial::SetMaskTexture(const std::shared_ptr<Texture>& maskTexture)
//{
//    m_maskTexture = maskTexture;
//}
//
//std::shared_ptr<Texture>& MaskTextureMaterial::GetMaskTexture() noexcept
//{
//    return m_maskTexture;
//}
//
//const std::shared_ptr<Texture>& MaskTextureMaterial::GetMaskTexture() const noexcept
//{
//    return m_maskTexture;
//}
////
///* @section Private variable */
//private:
//    std::shared_ptr<Texture> m_maskTexture;
//};

//class GrayTextureMaterial :
//    public TextureMaterial
//{
//public:
//    TGON_RUNTIME_OBJECT(GrayTextureMaterial);
//};
//


//GrayscaleTextureMaterial::GrayscaleTextureMaterial() :
//    TextureMaterial(std::make_shared<Shader>(g_positionUVVert, g_grayScaleTextureFrag))
//{
//}
//
//void GrayscaleTextureMaterial::Use()
//{
//    SuperType::Use();
//}
//
//void GrayscaleTextureMaterial::Unuse()
//{
//}
//
//bool GrayscaleTextureMaterial::CanBatch(const Material & rhs) const
//{
//    return false;
//}

} /* namespace tgon */
