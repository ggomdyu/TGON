/**
 * @filename    GenericGraphicsDevice.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace graphics
{

template <typename _DerivedType>
class TGON_API GenericGraphicsDevice :
    private boost::noncopyable
{
/* @section Ctor/Dtor */
public:
    explicit GenericGraphicsDevice() = default;
    ~GenericGraphicsDevice() = default;

/* @section Get method */
public:
    //const string::TFixedString& GetVideoCardDescription() const noexcept;

    //const TRefreshRate& GetRefreshRate() const noexcept;

    //uint32_t GetVendorId() const noexcept;

    /* @return  Current device's Video memory in MiB */
    //uint32_t GetVideoMemorySize() const noexcept;

/* @section Private variable */
protected:
};

} /* namespace graphics */
} /* namespace tgon */
