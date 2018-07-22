/**
 * @file    EventDispatcher.h
 * @author  ggomdyu
 * @since   05/19/2018
 */

#pragma once
#include <map>

#include "Core/Platform/Config.h"
#include "Core/Object/Delegate.h"
#include "Core/String/StringViewHash.h"

namespace tgon
{

class TGON_API EventDispatcher final
{
/* @section Public type */
public:
    using EventHandler = Delegate<void()>;
    
/* @section Public method */
public:
    void SubscribeEvent(const StringViewHash& eventName, const EventHandler& eventHandler);

    void SubscribeEvent(const StringViewHash& eventName, EventHandler&& eventHandler);
    
    bool UnsubscribeEvent(const StringViewHash& eventName, const EventHandler& eventHandler);
    
    void DispatchEvent(const StringViewHash& eventName);
    
/* @section Private variable */
private:
    std::map<size_t, std::map<uintptr_t, EventHandler>> m_eventHandlers;
};

} /* namespace tgon */
