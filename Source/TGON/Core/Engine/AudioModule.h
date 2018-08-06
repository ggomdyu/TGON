/**
 * @file    AudioModule.h
 * @author  ggomdyu
 * @since   08/06/2018
 */

#pragma once
#include "Core/Audio/AudioDevice.h"

#include "IModule.h"

namespace tgon
{

class TGON_API AudioModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(AudioModule);

/* @section Public constructor */
public:
    AudioModule();

/* @section Public destructor */
public:
    virtual ~AudioModule() override = default;

/* @section Public method */
public:
    /* @brief   Updates the module. */
    virtual void Update() override;
    
/* @section Private variable */
private:
    //AudioDevice m_audioDevice;
};

} /* namespace tgon */