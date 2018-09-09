/**
 * @file    MeshUtility.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Mesh.h"

namespace tgon
{

class TGON_API MeshUtility
{   
/* @section Public method */
public:
    /* @brief   Creates a triangle mesh which is global instance. */
    static std::shared_ptr<Mesh> CreateSharedTriangle();
                                  
    /* @brief   Creates a shared cube mesh which is global instance. */
    static std::shared_ptr<Mesh> CreateSharedCube();
                                  
    /* @brief   Creates a shared quad mesh which is global instance. */
    static std::shared_ptr<Mesh> CreateSharedQuad();

    //std::shared_ptr<Mesh> CreateUVSphere(int );
    
    /**
     * @brief   Returns the shared sphere mesh which is based on icosahedron.
     * @see     http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
     */
    //std::shared_ptr<Mesh> CreateIcoSphere(int );
};

} /* namespace tgon */
