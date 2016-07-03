/*
* Author : Cha Junho
* Date : 01/08/2016
* Latest author :
* Latest date : 
*/


#pragma once
#include "../Platform/Slate/PlatformGraphics.h"
#include "../Platform/Slate/PlatformFwd.h"

namespace tgon
{


using TGraphics = GraphicsImpl;
using SpTGraphics = std::shared_ptr<GraphicsImpl>;
using WpTGraphics = std::weak_ptr<GraphicsImpl>;


}