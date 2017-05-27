/**
 * @filename    GenericApplicationType.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include "Core/Object/TDelegate.h"

namespace tgon {
namespace platform {

using OkPopupEventHandler = object::TDelegate<void()>;
using YesNoPopupEventHandler = object::TDelegate<void(enum class YesNoPopupEvent)>;

} /* namespace platform */
} /* namespace tgon */