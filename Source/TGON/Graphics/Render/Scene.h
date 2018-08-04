/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   06/16/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/Platform/Config.h"

#include "Sprite.h"
#include "Batch.h"

namespace tgon
{
    
class TGON_API Scene :
    private boost::noncopyable
{
/* @section Public method */
public:
    void AddSprite(const std::shared_ptr<Sprite>& sprite);

/* @section Private variable */
private:
    BatchGroup m_batchGroup;
};

} /* namespace tgon */
