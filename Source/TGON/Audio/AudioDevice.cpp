#include "PrecompiledHeader.h"

#include <stdexcept>

#include "AudioDevice.h"

namespace tgon
{

AudioDevice::AudioDevice() :
    m_device(alcOpenDevice(nullptr))
{
    if (m_device == nullptr)
    {
        throw std::runtime_error("Failed to invoke alcOpenDevice.");
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (m_context == nullptr)
    {
        throw std::runtime_error("Failed to invoke alcCreateContext.");
    }
}

AudioDevice::AudioDevice(AudioDevice&& rhs) noexcept :
    m_context(rhs.m_context),
    m_device(rhs.m_device)
{
    rhs.m_context = nullptr;
    rhs.m_device = nullptr;
}

AudioDevice::~AudioDevice()
{
    if (m_context != nullptr)
    {
        // If the main context indicates m_context, then set it to nullptr.
        if (alcGetCurrentContext() == m_context)
        {
            alcMakeContextCurrent(nullptr);
        }

        alcDestroyContext(m_context);
    }

    if (m_device != nullptr)
    {
        alcCloseDevice(m_device);
    }
}

AudioDevice& AudioDevice::operator=(AudioDevice&& rhs) noexcept
{
    if (this == &rhs)
    {
        return *this;
    }

    m_context = rhs.m_context;
    m_device = rhs.m_device;

    rhs.m_context = nullptr;
    rhs.m_device = nullptr;

    return *this;
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