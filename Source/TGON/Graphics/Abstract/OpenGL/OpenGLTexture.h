/**
 * @filename    OpenGLTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include "../Generic/GenericTexture.h"

#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

class OpenGLTexture :
    public GenericTexture
{
/* @section Public constructor */
public:
    explicit OpenGLTexture(const std::string& filePath);

/* @section Public destructor */
public:
    virtual ~OpenGLTexture() override = default;

/* @section Public method */
public:
    virtual void Use() final override;
    virtual void Unuse() final override;
    virtual void SetFilterMode(TextureFilterMode filterMode) final override;
    virtual void SetAddressMode(TextureAddressMode addressMode) final override;

private:
    GLuint m_rawTextureHandle;

    GLint m_rawAddressMode;
    GLint m_rawFilterMode;
};

class Texture :
    public OpenGLTexture
{
/* @section Public constructor */
public:
    using OpenGLTexture::OpenGLTexture;
};

} /* namespace graphics */
} /* namespace tgon */
