#include "PrecompiledHeader.h"

#include "Audio.h"

namespace tg
{

Audio::Audio() :
    m_device({nullptr, [](ALCdevice* device)
    {
        alcCloseDevice(device);
    }}),
    m_context({nullptr, [](ALCcontext* context)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
    }})
{
}

void Audio::Update()
{
}

}
