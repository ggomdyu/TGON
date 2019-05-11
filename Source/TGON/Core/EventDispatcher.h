/**
 * @file    EventDispatcher.h
 * @author  ggomdyu
 * @since   05/19/2018
 */

#pragma once
#include <map>

#include "Platform/Config.h"
#include "Core/Delegate.h"
#include "String/StringHash.h"

namespace tgon
{

class TGON_API EventDispatcher final
{
/**@section Type */
public:
    using EventHandler = Delegate<void()>;
    
/**@section Method */
public:
    void SubscribeEvent(const StringViewHash& eventName, const EventHandler& eventHandler);
    void SubscribeEvent(const StringViewHash& eventName, EventHandler&& eventHandler);
    bool UnsubscribeEvent(const StringViewHash& eventName, const EventHandler& eventHandler);
    void DispatchEvent(const StringViewHash& eventName);
    
/**@section Variable */
private:
    std::map<size_t, std::map<uintptr_t, EventHandler>> m_eventHandlers;
};

} /* namespace tgon */
