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

class Triangle :
    public Mesh
{
/* @section Public constructor */
public:
    explicit Triangle(const SharedGraphicsContext& context);
};

class Cube :
    public Mesh
{
    /* @section Public constructor */
public:
    explicit Cube(const SharedGraphicsContext& context);
};

class Quad :
    public Mesh
{
/* @section Public constructor */
public:
    explicit Quad(const SharedGraphicsContext& context);
};


} /* namespace tgon */
