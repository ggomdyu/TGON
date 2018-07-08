/**
 * @file    MeshUtility.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once

namespace tgon
{
    
class Mesh;
          
/* @brief   Returns the shared triangle mesh. */
std::shared_ptr<Mesh> MakeTriangle();
                                  
/* @brief   Returns the shared cube mesh. */
std::shared_ptr<Mesh> MakeCube();
                                  
/* @brief   Returns the shared quad mesh. */
std::shared_ptr<Mesh> MakeQuad();

} /* namespace tgon */
