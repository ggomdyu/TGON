#pragma once

// Todo: Move to MaterialFwd.h!
namespace tgon
{
namespace rhi
{
class BaseRHI;
} /* namespace rhi */

namespace render
{
class Texture2D;
} /* namespace render */
} /* namespace tgon */

namespace tgon
{
namespace render
{

class Material
{
/* @section Public method */
public:
    virtual void BeginScene() = 0;
    virtual void Draw(rhi::BaseRHI* rhi) = 0;
}

class TexturedMaterial :
    public Material
{
public:
    virtual void BeginScene() override;
    virtual void Draw(rhi::BaseRHI* rhi) override;

    virtual void SetTexture(const std::shared_ptr<Texture2D>& texture);
    const std::shared_ptr<Texture2D>& GetTexture() const;

private:
    std::shared_ptr<Texture2D> m_texture;
};

class AlphaTexturedMaterial :
    public TexturedMaterial
{
public:
    virtual void BeginScene() override {}
    virtual void Draw(rhi::BaseRHI* rhi) override {}
};

} /* namespace render */
} /* namespace tgon */
