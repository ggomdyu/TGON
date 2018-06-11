/**
 * @filename    EventModule.h
 * @author      ggomdyu
 * @since       05/19/2018
 */

#pragma once
#include <map>

#include "Core/Object/Delegate.h"
#include "Core/String/StringViewHash.h"

#include "IModule.h"

namespace tgon
{

class TGON_API EventModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(EventModule);

/* @section Public type */
public:
    using EventHandler = Delegate<void()>;
    
/* @section Public destructor */
public:
    virtual ~EventModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void SubscribeEvent(const StringViewHash& eventType, const EventHandler& eventHandler);
    void SubscribeEvent(const StringViewHash& eventType, EventHandler&& eventHandler);
    bool UnsubscribeEvent(const StringViewHash& eventType, const EventHandler& eventHandler);
    void NotifyEvent(const StringViewHash& eventType);
    
/* @section Private variable */
private:
    std::map<size_t, std::map<uintptr_t, Delegate<void()>>> m_eventHandlers;
};

} /* namespace tgon */
