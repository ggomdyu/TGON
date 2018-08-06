#include "PrecompiledHeader.h"

#include "AudioDevice.h"

namespace tgon
{

AudioDevice::AudioDevice() :
    m_device(alcOpenDevice(nullptr))
{
    if (m_device == nullptr)
    {
        return;
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (m_context == nullptr)
    {
        return;
    }
}

AudioDevice::~AudioDevice()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

void AudioDevice::MakeCurrent()
{
    alcMakeContextCurrent(m_context);
}

ALCdevice* AudioDevice::GetDevice() noexcept
{
    return m_device;
}

const ALCdevice* AudioDevice::GetDevice() const noexcept
{
    return m_device;
}

ALCcontext* AudioDevice::GetContext() noexcept
{
    return m_context;
}

const ALCcontext* AudioDevice::GetContext() const noexcept
{
    return m_context;
}

} /* namespace tgon */