#pragma once

#include "Engine/Module.h"

namespace tg
{

class Audio :
	public Module
{
public:
    TGON_RTTI(Audio)

/* @section Constructor */
public:
    Audio();

/* @section Method */
public:
    void Update() override;

/* @section Variable */
private:
    std::unique_ptr<struct ALCdevice, void(*)(ALCdevice*)> m_device;
    std::unique_ptr<struct ALCcontext, void(*)(ALCcontext*)> m_context;
};

}
