/**
 * @file    AudioDevice.h
 * @author  ggomdyu
 * @since   08/06/2018
 */

#pragma once
#include "Core/NonCopyable.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <AL/alc.h>
#endif

namespace tgon
{

class AudioDevice final :
    private NonCopyable
{
/**@section Constructor */
public:
    AudioDevice();
    AudioDevice(AudioDevice&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioDevice();

/**@section Operator */
public:
    AudioDevice& operator=(AudioDevice&& rhs) noexcept;

/**@section Method */
public:
    void MakeCurrent();
    ALCdevice* GetDevice() noexcept;
    ALCcontext* GetContext() noexcept;
    const ALCdevice* GetDevice() const noexcept;
    const ALCcontext* GetContext() const noexcept;

private:
    void Destroy();

/**@section Variable */
private:
    ALCdevice* m_device = nullptr;
    ALCcontext* m_context = nullptr;
};

} /* namespace tgon */
