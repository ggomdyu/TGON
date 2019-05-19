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
    /**@brief   Binds this to the current device context. */
    void MakeCurrent();
    ALCdevice* GetDevice() noexcept;
    ALCcontext* GetContext() noexcept;
    const ALCdevice* GetDevice() const noexcept;
    const ALCcontext* GetContext() const noexcept;

private:
    void Destroy();

/**@brief   Private variable */
private:
    ALCdevice* m_device;
    ALCcontext* m_context;
};

} /* namespace tgon */
