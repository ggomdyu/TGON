#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Math/Color.h"
#include "Core/Object/Object.h"
#include "Graphics/LowLevelRender/Texture.h"
#include "Graphics/LowLevelRender/Shader.h"

#include "../LowLevelRender/Texture.h"

namespace tgon
{

class Material :
    public Object,
    private boost::noncopyable
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
    virtual bool CanBatch(const Material& rhs) const = 0;

    const std::shared_ptr<Shader>& GetShader() noexcept;

/* @section Protected variable */
protected:
    std::shared_ptr<Shader> m_shader;
};

class ColorMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(ColorMaterial);

/* @section Public constructor */
public:
    ColorMaterial();

/* @section Public destructor */
public:
    virtual ~ColorMaterial() = default;

/* @section Public method */
public:
    virtual void Use();
    virtual void Unuse();
    virtual bool CanBatch(const Material& rhs) const;
    void SetColor(const Color4f& color);

/* @section Private variable */
private:
    Color4f m_color;
};

class TextureMaterial :
    public Material
{
public:
    TGON_RUNTIME_OBJECT(TextureMaterial);

/* @section Public method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture);
    const std::shared_ptr<Texture>& GetTexture() const;

/* @section Private variable */
private:
    std::shared_ptr<Texture> m_texture;
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
