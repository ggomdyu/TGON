/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       03/15/2018
 * @brief
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "GraphicsContext.h"

namespace tgon
{

class GraphicsResource :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    explicit GraphicsResource(const SharedGraphicsContext& context);

/* @section Public destructor */
public:
    virtual ~GraphicsResource() = 0;

/* @section Public method */
public:
    SharedGraphicsContext& GetContext() noexcept;

/* @section Private variable */
private:
    SharedGraphicsContext m_context;
};

inline GraphicsResource::~GraphicsResource() = default;

inline GraphicsResource::GraphicsResource(const SharedGraphicsContext& context) :
    m_context(context)
{
}

inline SharedGraphicsContext& GraphicsResource::GetContext() noexcept
{
    return m_context;
}

} /* namespace tgon */
