/**
 * filename GenericApplicationFwd.h
 * author   ggomdyu
 * since    04/04/2017
 */

#pragma once
#include "./Core/Delegate/TDelegate.h"

namespace tgon
{

enum class TPopupEvent;

using OnPopupEventHandle = TDelegate<void(TPopupEvent)>;

} /* namespace tgon */