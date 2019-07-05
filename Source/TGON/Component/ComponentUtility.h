/**
 * @file    ComponentUtility.h
 * @author  ggomdyu
 * @since   06/18/2018
 */

#pragma once
#include "Core/DynamicCast.h"

namespace tgon
{

/**
 * @brief                   Gets the unique id of component specified by _ComponentType.
 * @tparam _ComponentType   The type of Component what you want to get id.
 * @return                  The unique id of component.
 */
template <typename _ComponentType>
inline std::size_t GetComponentId()
{
    return tgon::GetRTTI<_ComponentType>()->GetHashCode();
}

} /* namespace tgon */
