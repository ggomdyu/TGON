/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       11/12/2017
 * @brief
 */


#pragma once
#include "Mesh.h"
#include "Material.h"

namespace tgon
{

std::shared_ptr<Mesh> MakeTriangle(const std::shared_ptr<Material>& material);

std::shared_ptr<Mesh> MakeCube(const std::shared_ptr<Material>& material);

std::shared_ptr<Mesh> MakeQuad(const std::shared_ptr<Material>& material);

} /* namespace tgon */
