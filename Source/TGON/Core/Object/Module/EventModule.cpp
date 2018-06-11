#include "PrecompiledHeader.h"

#include "EventModule.h"

namespace tgon
{

void EventModule::Update()
{
}

void EventModule::SubscribeEvent(const StringViewHash& eventType, const EventHandler& eventHandler)
{
    m_eventHandlers[eventType.GetHashCode()][reinterpret_cast<uintptr_t>(&eventHandler)] = eventHandler;
}
    
void EventModule::SubscribeEvent(const StringViewHash& eventType, EventHandler&& eventHandler)
{
    m_eventHandlers[eventType.GetHashCode()][reinterpret_cast<uintptr_t>(&eventHandler)] = std::move(eventHandler);
}
    
bool EventModule::UnsubscribeEvent(const StringViewHash& eventType, const EventHandler& eventHandler)
{
    auto iter = m_eventHandlers.find(eventType.GetHashCode());
    if (iter == m_eventHandlers.end())
    {
        return false;
    }
    
    iter->second.erase(reinterpret_cast<uintptr_t>(&eventHandler));
    
    return true;
}
    
void EventModule::NotifyEvent(const StringViewHash& eventType)
{
    auto iter = m_eventHandlers.find(eventType.GetHashCode());
    if (iter == m_eventHandlers.end())
    {
        return;
    }
    
    for (auto& handler : iter->second)
    {
        handler.second();
    }
}
    
} /* namespace tgon */
