/**
 * @file    AudioModule.h
 * @author  ggomdyu
 * @since   08/06/2018
 */

#pragma once
#include "Audio/AudioDevice.h"

#include "Module.h"

namespace tgon
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

} /* namespace tgon */
