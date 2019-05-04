#include "PrecompiledHeader.h"

#if TGON_USING_OPENGL
#   include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#endif

#include "Material.h"

namespace tgon
{

Material::Material(const std::shared_ptr<ShaderProgram>& shader) :
    m_shader(shader)
{
}

void Material::SetWVP(const Matrix4x4& matWVP)
{
    m_shader->SetParameterMatrix4fv("g_uWVP", matWVP[0]);
}

std::shared_ptr<ShaderProgram>& Material::GetShader() noexcept
{
    return m_shader;
}

const std::shared_ptr<ShaderProgram>& Material::GetShader() const noexcept
{
    return m_shader;
}

ColorMaterial::ColorMaterial(const Color3f& blendColor) :
    ColorMaterial(std::make_shared<ShaderProgram>(g_positionColorVert, g_positionColorFrag), blendColor)
{
}

ColorMaterial::ColorMaterial() :
    ColorMaterial(Color3f(1.0f, 1.0f, 1.0f))
{
}

ColorMaterial::ColorMaterial(const std::shared_ptr<ShaderProgram>& shader, const Color3f& blendColor) :
    Material(shader),
    m_blendColor(blendColor)
{
}

void ColorMaterial::Use()
{
    m_shader->Use();
    m_shader->SetParameter4f("g_uColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, 1.0f);
}

void ColorMaterial::Unuse()
{
    m_shader->Unuse();
}

bool ColorMaterial::CanBatch(const Material& rhs) const
{
    const ColorMaterial* rhs2 = DynamicCast<const ColorMaterial*>(&rhs);
    if (rhs2 != nullptr)
    {
        return m_blendColor == rhs2->m_blendColor;
    }
    else
    {
        return false;
    }
}

void ColorMaterial::SetBlendColor(const Color3f& blendColor)
{
    m_blendColor = blendColor;
}

Color3f& ColorMaterial::GetBlendColor() noexcept
{
    return m_blendColor;
}

const Color3f& ColorMaterial::GetBlendColor() const noexcept
{
    return m_blendColor;
}

TextureMaterial::TextureMaterial() :
    TextureMaterial(nullptr)
{
}

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& texture, const Color3f& blendColor, float opacity) :
    TextureMaterial(std::make_shared<ShaderProgram>(g_positionUVVert, g_positionUVFrag), texture, blendColor, opacity)
{
}

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& texture) :
    TextureMaterial(texture, Color3f(1.0f, 1.0f, 1.0f), 1.0f)
{
}

TextureMaterial::TextureMaterial(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Texture>& texture, const Color3f& blendColor, float opacity) :
    ColorMaterial(shader, blendColor),
    m_texture(texture),
    m_opacity(opacity)
{
}

void TextureMaterial::Use()
{
    m_shader->Use();
    m_shader->SetParameter4f("g_uColor", m_blendColor.r, m_blendColor.g, m_blendColor.b, m_opacity);

    m_texture->Use();
}

void TextureMaterial::Unuse()
{
}

bool TextureMaterial::CanBatch(const Material& rhs) const
{
    const TextureMaterial* rhs2 = DynamicCast<const TextureMaterial*>(&rhs);
    if (rhs2 != nullptr)
    {
        return m_blendColor == rhs2->m_blendColor /*&&
               m_texture->GetID() == rhs2->m_texture->GetID()*/;
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

const std::shared_ptr<Texture>& TextureMaterial::GetTexture() noexcept
{
    return m_texture;
}

std::shared_ptr<const Texture> TextureMaterial::GetTexture() const noexcept
{
    return m_texture;
}

void TextureMaterial::SetOpacity(float opacity) noexcept
{
    m_opacity = opacity;
}

float& TextureMaterial::GetOpacity() noexcept
{
    return m_opacity;
}

const float TextureMaterial::GetOpacity() const noexcept
{
    return m_opacity;
}

} /* namespace tgon */
