#pragma once

namespace tgon
{
namespace render
{

enum class TextureAdressMode
{
    Wrap,
    Border,
    Clamp,
    Mirror,
}

class Texture2D
{
/* @section Public constructor */
public:
    explicit Texture2D(const char* imageFilePath);

/* @section Public method */
public:
    uint32_t GetHeight() const noexcept;
    uint32_t GetWidth() const noexcept;

/* @section Private variable */
private:
    uint8_t* m_textureBits;
    uint32_t m_width;
    uint32_t m_height;
};

} /* namespace render */
} /* namespace tgon */
