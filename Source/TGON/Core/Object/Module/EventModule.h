/**
 * @filename    EventModule.h
 * @author      ggomdyu
 * @since       05/19/2018
 */

#pragma once
#include <map>

#include "Core/Object/Delegate.h"
#include "Core/String/StringHash.h"

#include "IModule.h"

namespace tgon
{

class TGON_API EventModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(EventModule)

/* @section Public type */
public:
    using EventHandler = Delegate<void()>;
    
/* @section Public destructor */
public:
    virtual ~EventModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void SubscribeEvent(const StringHash& eventType, const StringHash& observerName, const EventHandler& handler);
    void SubscribeEvent(const StringHash& eventType, const StringHash& observerName, EventHandler&& handler);
    void UnsubscribeEvent(const StringHash& eventType, const StringHash& observerName);
    void NotifyEvent(const StringHash& eventType);
    
/* @section Private variable */
private:
    std::map<size_t, std::map<size_t, EventHandler>> m_eventHandlerMap;
};

} /* namespace tgon */
