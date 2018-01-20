/**
 * @filename    TextureUtility.h
 * @author      ggomdyu
 * @since       12/09/2017
 */

#pragma once
#include <cstdlib>
#include <vector>

namespace tgon
{
namespace graphics
{

bool LoadPNG(const char* filePath, std::vector<uint8_t>* destBuffer, std::size_t* width, std::size_t* height);

bool LoadJPG(const char* filePath, std::vector<uint8_t>* destBuffer, std::size_t* width, std::size_t* height);

bool LoadWebP(const char* filePath, std::vector<uint8_t>* destBuffer, std::size_t* width, std::size_t* height);

} /* namespace graphics */
} /* namespace tgon */