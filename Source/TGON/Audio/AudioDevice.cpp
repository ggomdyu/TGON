#include "PrecompiledHeader.h"

#include <stdexcept>

#include "AudioDevice.h"

#pragma comment(lib, "Winmm.lib")

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
    this->Destroy();
}

AudioDevice& AudioDevice::operator=(AudioDevice&& rhs) noexcept
{
    this->Destroy();

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

void AudioDevice::Destroy()
{
    if (m_context != nullptr)
    {
        // If the current context indicates m_context, then set it to nullptr.
        if (alcGetCurrentContext() == m_context)
        {
            alcMakeContextCurrent(nullptr);
        }

        alcDestroyContext(m_context);
    }

    if (m_device != nullptr)
    {
        alcCloseDevice(m_device);
        m_device = nullptr;
    }
}

} /* namespace tgon */
