/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       12/09/2017
 */

#pragma once
#include <cstdlib>
#include <string>

namespace tgon
{
namespace graphics
{

enum class TextureAddressMode
{
    Wrap,
    Border,
    Clamp,
    Mirror,
};

class Texture2D
{
/* @section Public constructor */
public:
    explicit Texture2D(const std::string& filePath);
    explicit Texture2D(std::string&& filePath);

/* @section Public method */
public:
    const std::string& GetFilePath() const noexcept;
    uint8_t* GetTextureBits() noexcept;
    uint32_t GetHeight() const noexcept;
    uint32_t GetWidth() const noexcept;

/* @section Private variable */
private:
    std::string m_filePath;
    uint8_t* m_textureBits;
    uint32_t m_width;
    uint32_t m_height;
};

} /* namespace graphics */
} /* namespace tgon */
