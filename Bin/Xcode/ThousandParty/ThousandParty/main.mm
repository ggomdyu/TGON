#include <iostream>
#include <ctime>
#include <cmath>

#import "Core/Platform/Application.h"

class TGON_API ModelJoy :
    public tgon::platform::Application
{
public:
    virtual void OnLaunch() override
    {
        int n = 3;
    }

    virtual void OnTerminate() override
    {
        int n = 3;
    }

    virtual void OnUpdate() override
    {

    }
    virtual void OnDraw() override
    {
    }
};

TGON_DECLARE_APPLICATION(ModelJoy)
