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

class Quad :
    public Mesh
{
/* @section Public constructor */
public:
    explicit Quad(const SharedGraphicsContext& context);
    virtual ~Quad() override = default;

public:
};

} /* namespace tgon */
