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
    
/**@section Protected constructor */
protected:
    explicit Material(const std::shared_ptr<Shader>& shader);

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
    std::shared_ptr<Shader>& GetShader() noexcept;
    
    /**@brief   Gets a shader managed by this material. */
    const std::shared_ptr<Shader>& GetShader() const noexcept;
    
/**@section Protected variable */
protected:
    std::shared_ptr<Shader> m_shader;
};

class TGON_API ColorMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(ColorMaterial);

/**@section Public constructor */
public:
    ColorMaterial(const Color3f& blendColor);
    ColorMaterial();

/**@section Protected constructor */
protected:
    ColorMaterial(const std::shared_ptr<Shader>& shader, const Color3f& blendColor);
    
/**@section Public destructor */
public:
    virtual ~ColorMaterial() override = default;

/**@section Public method */
public:
    virtual void Use() override;
    virtual void Unuse() override;

    /**@brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const override;

    /**@brief   Sets the blend color of this material. */
    void SetBlendColor(const Color3f& blendColor);

    /**@brief   Gets the blend color of this material. */
    Color3f& GetBlendColor() noexcept;

    /**@brief   Gets the blend color of this material. */
    const Color3f& GetBlendColor() const noexcept;

/**@section Protected variable */
protected: 
    Color3f m_blendColor;
    float m_opacity;
};
    
//class TGON_API StandardMaterial :
//    public Material
//{
//public:
//    void SetDiffuseColor(const Color3f& diffuseColor);
//    void SetSpecularColor(const Color3f& specularColor);
//    void SetAmbientColor(const Color3f& ambientColor);
//};

class TGON_API TextureMaterial :
    public ColorMaterial
{
public:
    TGON_RUNTIME_OBJECT(TextureMaterial);

/**@section Public constructor */
public:
    TextureMaterial();
    TextureMaterial(const std::shared_ptr<Texture>& texture, const Color3f& blendColor, float opacity);
    TextureMaterial(const std::shared_ptr<Texture>& texture);

/**@section Protected constructor */
protected:
    TextureMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const Color3f& blendColor, float opacity);

/**@section Public destructor */
public:
    virtual ~TextureMaterial() override = default;

/**@section Public method */
public:
    virtual void Use() override;
    virtual void Unuse() override;
    
    /**@brief   Checks whether the specified material can batched. */
    virtual bool CanBatch(const Material& rhs) const override;
    
    /**@brief   Sets the texture of this material. */
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;

    /**@brief   Gets the texture of this material. */
    const std::shared_ptr<Texture>& GetTexture() noexcept;

    /**@brief   Gets the texture of this material. */
    std::shared_ptr<const Texture> GetTexture() const noexcept;

    /**@brief   Gets the opacity of this material. */
    void SetOpacity(float opacity) noexcept;

    /**@brief   Gets the opacity of this material. */
    float& GetOpacity() noexcept;

    /**@brief   Gets the opacity of this material. */
    const float GetOpacity() const noexcept;
    
/**@section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
    float m_opacity;
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
///**@section Public constructor */
//public:
//    GrayscaleTextureMaterial();
//
//    /**@section Public destructor */
//public:
//    virtual ~GrayscaleTextureMaterial() override = default;
//
//    /**@section Public method */
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
///**@section Public constructor */
//public:
//    MaskTextureMaterial() = default;
//
///**@section Public destructor */
//public:
//    virtual ~MaskTextureMaterial() override = default;
//
///**@section Public method */
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
///**@section Private variable */
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
