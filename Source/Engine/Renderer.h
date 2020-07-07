#pragma once

#include "Graphics/Graphics.h"

#include "Module.h"

namespace tg
{

class Renderer final :
	public Module
{
public:
    TGON_RTTI(Renderer)

/**@section Constructor */
public:
    Renderer(void* nativeWindow, const VideoMode& videoMode);

/**@section Method */
public:
    void Update() override;

/**@section Variable */
private:
    Graphics m_graphics;
};

}
