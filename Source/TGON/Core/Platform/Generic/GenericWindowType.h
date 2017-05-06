/**
 * @filename    GenericWindowType.h
 * @author      ggomdyu
 * @since       05/05/2017
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon {
namespace platform {

enum class MouseType
{
	Left,
	Middle,
	Right,
};

struct WindowStyle
{
public:
	std::string caption = u8"Hello World!";

	std::size_t x = 100;
	std::size_t y = 100;
	std::size_t width = 500;
	std::size_t height = 500;

	bool popup = false;
	bool fullScreen = false;
	bool supportWindowTransparency = false;
	bool supportPerPixelTransparency = false;
	bool resizeable = true;
    bool topMost = false;
    bool maximized = false;
	bool minimized = false;
    bool showMiddle = true;
    bool showImmediately = true;
};

} /* namespace platform */
} /* namespace tgon */