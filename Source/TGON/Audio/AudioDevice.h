/**
 * @file    AudioDevice.h
 * @author  ggomdyu
 * @since   08/06/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <alc.h>
#endif

namespace tgon
{

class TGON_API AudioDevice final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    AudioDevice() noexcept(false);
    AudioDevice(AudioDevice&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioDevice();

/**@section Operator */
public:
    AudioDevice& operator=(AudioDevice&& rhs) noexcept;

public:
    /**@brief   Makes this device's context the current context. */
    void MakeCurrent();

    /**@brief   Gets the device. */
    ALCdevice* GetDevice() noexcept;

    /**@brief   Gets the device. */
    const ALCdevice* GetDevice() const noexcept;

    /**@brief   Gets the context. */
    ALCcontext* GetContext() noexcept;

    /**@brief   Gets the context. */
    const ALCcontext* GetContext() const noexcept;

/**@brief   Private variable */
private:
    ALCdevice* m_device;

    ALCcontext* m_context;
};

} /* namespace tgon */
