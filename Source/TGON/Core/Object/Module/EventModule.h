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

class TGON_API EventObserver
{
/* @section Public type */
public:
    using EventHandler = Delegate<void()>;
    
/* @section Public constructor */
public:
    EventObserver(const StringHash& observerName, const EventHandler& handler);
    EventObserver(const StringHash& observerName, EventHandler&& handler);
    
private:
    size_t m_observerNameHash;
    EventHandler m_eventHandler;
}
    
class TGON_API EventModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(EventModule)

/* @section Public type */
private:
    using EventHandler = Delegate<void()>;
    
/* @section Public constructor */
public:
    EventModule();

/* @section Public destructor */
public:
    virtual ~EventModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void SubscribeEvent(const StringHash& eventType, const EventObserver& handler);
    void SubscribeEvent(const StringHash& eventType, EventObserver&& handler);
    void NotifyEvent(const StringHash& eventType);
    
/* @section Private variable */
private:
    std::map<size_t, std::vector<EventObserver>> m_eventHandlerMap;
};

} /* namespace tgon */
