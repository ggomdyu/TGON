/**
 * @filename    GenericApplicationType.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include "Core/Object/TDelegate.h"

namespace tgon {
namespace platform {

enum class YesNoPopupEvent;

using OkPopupEventHandler = object::TDelegate<void()>;
using YesNoPopupEventHandler = object::TDelegate<void(YesNoPopupEvent)>;

} /* namespace platform */
} /* namespace tgon */