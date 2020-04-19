#pragma once

#include "Audio/AudioDevice.h"

#include "Module.h"

namespace tg
{

class AudioModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(AudioModule)

/* @section Constructor */
public:
    AudioModule();

/* @section Variable */
private:
    AudioDevice m_audioDevice;
};

}
