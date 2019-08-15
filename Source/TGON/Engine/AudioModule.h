/**
 * @file    AudioModule.h
 * @author  ggomdyu
 * @since   08/06/2018
 */

#pragma once
#include "Audio/AudioDevice.h"

#include "IModule.h"

namespace tgon
{

class TGON_API AudioModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(AudioModule);

/* @section Constructor */
public:
    AudioModule();

/* @section Destructor */
public:
    virtual ~AudioModule() override = default;

/* @section Method */
public:
    /* @brief   Updates the module. */
    virtual void Update() override;
    
/* @section Variable */
private:
    //AudioDevice m_audioDevice;
};

}
