#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"

#include "AudioModule.h"

namespace tgon
{

AudioModule::AudioModule() :
    m_audioDevice([]()
    {
        auto audioDevice = AudioDevice::Create();
        if (audioDevice.has_value() == false)
        {
            Debug::Fail("Failed to create AudioDevice.");
        }

        return std::move(audioDevice.value());
    } ())
{
}

} /* namespace tgon */
