/*
* Author : Junho-Cha
* Date : 04/28/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <memory>

namespace tgon
{


class WindowsWindow;
using WindowImpl = WindowsWindow;

class TWindow;
using SpTWindow = std::shared_ptr<TWindow>;
using WpTWindow = std::weak_ptr<TWindow>;

using TMsgCallback = int32_t(*)( TWindow*, enum class WindowEvent );


}