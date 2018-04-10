#pragma once
#include "../LowLevelRender/Texture.h"

#include "Core/Math/Color.h"

namespace tgon
{

/**
 * @class   Material
 * @brief   The base of all material.
 */
class Material
{
/* @section Public method */
public:
    virtual void Use() = 0;
    virtual void Unuse() = 0;
    virtual bool CanBatch(const Material& rhs) = 0;

private:
};

/**
 * @class   TextureMaterial
 * @brief   Material that uses a texture.
 */
class TextureMaterial :
    public Material
{
};

/**
 * @class   GrayTextureMaterial
 * @brief   Material that uses a grayscale texture.
 */
class GrayTextureMaterial :
    public TextureMaterial
{
};

class UberMaterial :
    public Material
{
};

} /* namespace tgon */
