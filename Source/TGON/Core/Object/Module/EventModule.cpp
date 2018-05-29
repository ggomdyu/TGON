#include "PrecompiledHeader.h"

#include "EventModule.h"

namespace tgon
{

EventModule::EventModule()
{
}

void EventModule::Update()
{
}

void EventModule::SubscribeEvent(const StringHash& eventType, const EventHandler& handler)
{
    m_eventHandlerMap[eventType.GetHashCode()].push_back(handler);
}
    
void EventModule::SubscribeEvent(const StringHash& eventType, EventHandler&& handler)
{
    m_eventHandlerMap[eventType.GetHashCode()].push_back(std::move(handler));
}
    
void EventModule::NotifyEvent(const StringHash& eventType)
{
    auto iter = m_eventHandlerMap.find(eventType.GetHashCode());
    if (iter != m_eventHandlerMap.end())
    {
        for (auto& handler : iter->second)
        {
            handler();
        }
    }
}
    
} /* namespace tgon */
