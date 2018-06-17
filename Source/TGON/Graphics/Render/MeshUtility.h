/**
 * @filename    MeshUtility.h
 * @author      ggomdyu
 * @since       01/06/2018
 */

#pragma once
#include "Mesh.h"
#include "Material.h"

namespace tgon
{

std::shared_ptr<Mesh> MakeTriangle(std::shared_ptr<Material> material);

std::shared_ptr<Mesh> MakeCube(std::shared_ptr<Material> material);

std::shared_ptr<Mesh> MakeQuad(std::shared_ptr<Material> material);

} /* namespace tgon */
