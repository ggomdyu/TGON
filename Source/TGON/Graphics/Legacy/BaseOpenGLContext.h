/**
 * @filename    BaseOpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{
namespace opengl
{

class TGON_API BaseOpenGLContext
{
/* @section Public destructor */
public:
    virtual ~BaseOpenGLContext() = default;

/* @section Public method */
public:
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
};

} /* namespace opengl */
} /* namespace tgon */
