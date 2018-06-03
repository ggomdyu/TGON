/**
 * @filename    SpriteBatch.h
 * @author      ggomdyu
 * @since       06/03/2018
 */

#pragma once
#include "Mesh.h"
#include "Material.h"

namespace tgon
{
    
class SpriteBatch
{
public:
    
/* @section Private variable */
private:ㅇ    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
};
    
} /* namespace tgon */
