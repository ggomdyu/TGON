#include "PrecompiledHeader.h"

#if TGON_USING_OPENGL
#   include "Graphics/LowLevel/OpenGL/OpenGLShaderCode.h"
#endif

#include "Material.h"

namespace tgon
{

ColorMaterial::ColorMaterial(const Color4f& blendColor) :
    ColorMaterial(std::make_shared<Shader>(g_positionColorVert, g_positionColorFrag), blendColor)
{
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

TextureMaterial::TextureMaterial(const std::shared_ptr<Texture>& texture, const Color4f& blendColor) :
    TextureMaterial(std::make_shared<Shader>(g_positionUVVert, g_positionUVFrag), texture, blendColor)
{
}

bool TextureMaterial::CanBatch(const Material& rhs) const
{
    const TextureMaterial* rhs2 = DynamicCast<const TextureMaterial*>(&rhs);
    if (rhs2 != nullptr)
    {
        return m_blendColor == rhs2->m_blendColor &&
               m_texture->GetFilePath() == rhs2->m_texture->GetFilePath();
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
