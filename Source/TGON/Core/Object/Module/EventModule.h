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

/* @section Public destructor */
public:
    virtual ~EventModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void SubscribeEvent(const StringViewHash& eventType, const StringViewHash& observerName, const Delegate<void()>& handler);
    void SubscribeEvent(const StringViewHash& eventType, const StringViewHash& observerName, Delegate<void()>&& handler);
    void UnsubscribeEvent(const StringViewHash& eventType, const StringViewHash& observerName);
    void NotifyEvent(const StringViewHash& eventType);
    
/* @section Private variable */
private:
    std::map<size_t, std::map<size_t, Delegate<void()>>> m_eventHandlerMap;
};

} /* namespace tgon */
