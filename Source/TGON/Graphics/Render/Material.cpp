#include "PrecompiledHeader.h"

#if TGON_USING_OPENGL
#   include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#endif

#include "Material.h"

namespace tgon
{

Material::Material(const std::shared_ptr<Shader>& shader) :
    m_shader(shader)
{
}

ColorMaterial::ColorMaterial() :
    Material(std::make_shared<Shader>(g_positionColorVert, g_positionColorFrag)),
    m_color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

void ColorMaterial::Use()
{
    m_shader->Use();
    m_shader->SetParameter4f("g_uColor", m_color.r, m_color.g, m_color.b, m_color.a);
}

void ColorMaterial::Unuse()
{
    m_shader->Unuse();
}

bool ColorMaterial::CanBatch(const Material& rhs) const
{
    const ColorMaterial* material = DynamicCast<const ColorMaterial*>(&rhs);
    if (material != nullptr)
    {
        return m_color == material->m_color;
    }
    else
    {
        return false;
    }
}

void Material::SetWVP(const Matrix4x4& matWVP)
{
    m_shader->SetParameterMatrix4fv("g_uWVP", matWVP[0]);
}

std::shared_ptr<Shader>& Material::GetShader() noexcept
{
    return m_shader;
}

const std::shared_ptr<Shader>& Material::GetShader() const noexcept
{
    return m_shader;
}
    
void ColorMaterial::SetColor(const Color4f& color)
{
    m_color = color;
}

const Color4f& ColorMaterial::GetColor() const noexcept
{
    return m_color;
}

TextureMaterial::TextureMaterial() :
    TextureMaterial(nullptr)
{
}

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& texture, const Color4f& blendColor) :
    Material(std::make_shared<Shader>(g_positionUVVert, g_positionUVFrag)),
    m_texture(texture),
    m_blendColor(blendColor)
{
}

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& texture) :
    Material(std::make_shared<Shader>(g_positionUVVert, g_positionUVFrag)),
    m_texture(texture),
    m_blendColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f))
{
}

void TextureMaterial::Use()
{
    m_shader->Use();
    m_shader->SetParameter4f("g_uBlendColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, m_blendColor.a);
    
    m_texture->Use();
}

void TextureMaterial::Unuse()
{
}

bool TextureMaterial::CanBatch(const Material& rhs) const
{
    const TextureMaterial* material = DynamicCast<const TextureMaterial*>(&rhs);
    if (material != nullptr)
    {
        return m_blendColor == material->m_blendColor &&
               m_texture->GetFilePath() == material->m_texture->GetFilePath();
    }
    else
    {
        return false;
    }
}

void TextureMaterial::SetTexture(const std::shared_ptr<Texture>& texture) noexcept
{
    m_texture = texture;
}

std::shared_ptr<Texture>& TextureMaterial::GetTexture() noexcept
{
    return m_texture;
}
    
const std::shared_ptr<Texture>& TextureMaterial::GetTexture() const noexcept
{
    return m_texture;
}

void TextureMaterial::SetBlendColor(const Color4f& blendColor) noexcept
{
    m_blendColor = blendColor;
}

Color4f& TextureMaterial::GetBlendColor() noexcept
{
    return m_blendColor;
}
    
const Color4f& TextureMaterial::GetBlendColor() const noexcept
{
    return m_blendColor;
}

void MaskTextureMaterial::Use()
{
}

void MaskTextureMaterial::Unuse()
{
}

bool MaskTextureMaterial::CanBatch(const Material& rhs) const
{
    return false;
}

void MaskTextureMaterial::SetMaskTexture(const std::shared_ptr<Texture>& maskTexture)
{
    m_maskTexture = maskTexture;
}

std::shared_ptr<Texture>& MaskTextureMaterial::GetMaskTexture() noexcept
{
    return m_maskTexture;
}
    
const std::shared_ptr<Texture>& MaskTextureMaterial::GetMaskTexture() const noexcept
{
    return m_maskTexture;
}

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
