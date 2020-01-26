/**
 * @file    MeshUtility.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include "Mesh.h"

namespace tgon
{

/**@brief   Creates a triangle mesh which is global instance. */
TGON_API std::shared_ptr<Mesh> GetSharedTriangle();
                                  
/**@brief   Creates a shared cube mesh which is global instance. */
TGON_API std::shared_ptr<Mesh> GetSharedCube();
                                  
/**@brief   Creates a shared quad mesh which is global instance. */
/**@todo    Return type should be changed to std::shared_ptr<const Mesh> */
TGON_API std::shared_ptr<Mesh> GetSharedQuad();
 
/**
 * @brief   Returns the shared sphere mesh which is based on icosahedron.
 * @see     http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
 */
//std::shared_ptr<Mesh> CreateIcoSphere(int );

} /* namespace tgon */
