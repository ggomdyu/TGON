#include "PrecompiledHeader.pch"

#if TGON_USING_OPENGL
#   include "Graphics/LowLevelRender/OpenGL/OpenGLShaderCode.h"
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

    return false;
}

const std::shared_ptr<Shader>& Material::GetShader() noexcept
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
    Material(std::make_shared<Shader>(g_positionUVVert, g_positionUVFrag)),
    m_blendColor(1.0f, 1.0f, 1.0f, 1.0f)
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

bool TextureMaterial::CanBatch(const Material & rhs) const
{
    return false;
}

void TextureMaterial::SetTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;
}

const std::shared_ptr<Texture>& TextureMaterial::GetTexture() const
{
    return m_texture;
}

void TextureMaterial::SetBlendColor(const Color4f& blendColor)
{
    m_blendColor = blendColor;
}

const Color4f& TextureMaterial::GetBlendColor() const noexcept
{
    return m_blendColor;
}

} /* namespace tgon */