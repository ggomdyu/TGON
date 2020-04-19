#include "PrecompiledHeader.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <AL/alc.h>
#endif

#include "AudioDevice.h"
#include "OpenALDebug.h"

#ifdef _MSC_VER
#   pragma comment(lib, "Winmm.lib")
#endif

namespace tg
{

AudioDevice::AudioDevice(const std::shared_ptr<ALCdevice>& device, const std::shared_ptr<ALCcontext>& context) noexcept :
    m_device(device),
    m_context(context)
{
    this->MakeCurrent();
}

std::optional<AudioDevice> AudioDevice::Create()
{
    std::shared_ptr<ALCdevice> device(alcOpenDevice(nullptr), [](ALCdevice* device)
    {
        alcCloseDevice(device);
    });
    if (device == nullptr)
    {
        return {};
    }

    std::shared_ptr<ALCcontext> context(alcCreateContext(device.get(), nullptr), [](ALCcontext* context)
    {
        if (alcGetCurrentContext() == context)
        {
            alcMakeContextCurrent(nullptr);
        }
        
        alcDestroyContext(context);
    });
    if (context == nullptr)
    {
        return {};
    }

    return AudioDevice(device, context);
}

void AudioDevice::MakeCurrent()
{
    TGON_AL_ERROR_CHECK(alcMakeContextCurrent(m_context.get()));
}

std::shared_ptr<ALCdevice> AudioDevice::GetDevice() noexcept
{
    return m_device;
}

std::shared_ptr<const ALCdevice> AudioDevice::GetDevice() const noexcept
{
    return m_device;
}

std::shared_ptr<ALCcontext> AudioDevice::GetContext() noexcept
{
    return m_context;
}

std::shared_ptr<const ALCcontext> AudioDevice::GetContext() const noexcept
{
    return m_context;
}

}
