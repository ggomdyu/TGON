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
    virtual ~OpenGLTexture() override;

/* @section Public method */
public:
    virtual void TransferToVideo() final override;
    virtual void UpdateParemeters() final override;

    virtual void SetFilterMode(TextureFilterMode filterMode) final override;
    virtual void SetWrapMode(TextureWrapMode addressMode) final override;
    virtual TextureFilterMode GetFilterMode() const noexcept final override;
    virtual TextureWrapMode GetWrapMode() const noexcept final override;

private:
    GLuint GenerateTexture() const;

private:
    GLuint m_textureHandle;

    GLint m_addressMode;
    GLint m_filterMode;
};

class Texture :
    public OpenGLTexture
{
/* @section Public constructor */
public:
    using OpenGLTexture::OpenGLTexture;

/* @section Public destructor */
public:
    virtual ~Texture() final override = default;
};

} /* namespace graphics */
} /* namespace tgon */
