#include "PrecompiledHeader.h"

#include "EventModule.h"

namespace tgon
{

void EventModule::Update()
{
}

void EventModule::SubscribeEvent(const StringHash& eventType, const StringHash& observerName, const Delegate<void()>& handler)
{
    m_eventHandlerMap[eventType.GetHashCode()][observerName.GetHashCode()] = handler;
}
    
void EventModule::SubscribeEvent(const StringHash& eventType, const StringHash& observerName, Delegate<void()>&& handler)
{
    m_eventHandlerMap[eventType.GetHashCode()][observerName.GetHashCode()] = std::move(handler);
}
    
void EventModule::UnsubscribeEvent(const StringHash& eventType, const StringHash& observerName)
{
    auto iter = m_eventHandlerMap.find(eventType.GetHashCode());
    if (iter == m_eventHandlerMap.end())
    {
        return;
    }
    
    iter->second.erase(observerName.GetHashCode());
}
    
void EventModule::NotifyEvent(const StringHash& eventType)
{
    auto iter = m_eventHandlerMap.find(eventType.GetHashCode());
    if (iter == m_eventHandlerMap.end())
    {
        return;
    }
    
    for (auto& handler : iter->second)
    {
        handler.second();
    }
}
    
} /* namespace tgon */
