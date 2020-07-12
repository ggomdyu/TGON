#pragma once

#include "Graphics/Graphics.h"

#include "Module.h"

namespace tg
{

class RendererModule final :
	public Module
{
public:
    TGON_RTTI(RendererModule)

/**@section Constructor */
public:
    RendererModule(void* nativeWindow, const VideoMode& videoMode);

/**@section Method */
public:
    void Update() override;
    [[nodiscard]] Graphics& GetGraphics() noexcept;
    [[nodiscard]] const Graphics& GetGraphics() const noexcept;

/**@section Variable */
private:
    Graphics m_graphics;
};

}
