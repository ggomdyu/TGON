#include "PrecompiledHeader.h"

#include "TGON.h"

class TGON_API ThousandParty final :
    public tgon::Application
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

/* @section Public constructor */
public:
    ThousandParty() :
        Application(tgon::WindowStyle())
    {
        this->AddModule<tgon::TimeModule>();
        this->AddModule<tgon::TaskModule>();
        this->AddModule<tgon::GraphicsModule>(tgon::VideoMode(), this->GetRootWindow());
        
        auto eventModule = this->AddModule<tgon::EventModule>();
        eventModule->SubscribeEvent(u8"PrintLogIsMYLOVE0", [&]()
        {
            tgon::Log(tgon::LogLevel::Debug, "Debug");
        });
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
    }

/* @section Public event handler */
public:
    virtual void OnWillLaunch() override
    {
        SuperType::OnWillLaunch();
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
    }

    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
        
        this->GetModule<tgon::EventModule>()->NotifyEvent("PrintLogIsMYLOVE0");
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
