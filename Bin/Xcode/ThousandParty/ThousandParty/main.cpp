#include <iostream>
#include <ctime>
#include <cmath>

#include "Core/Platform/Application.h"
#include "Core/Platform/Window.h"
#include "Core/Platform/Screen.h"

class TGON_API ModelJoy :
    public tgon::platform::Application
{
private:
    tgon::platform::Window m_window;

public:
    ModelJoy() :
        m_window([&]()
        {
            srand(time(nullptr));

            auto mainScreen = tgon::platform::GetMainScreen();

            tgon::platform::WindowStyle wndStyle;
            wndStyle.caption = u8"애플리케이숑";
            wndStyle.resizeable = false;
            wndStyle.x = rand() % (mainScreen.width - wndStyle.width);
            wndStyle.y = rand() % (mainScreen.height - wndStyle.height);
            return wndStyle;
        }())
    {

        auto d = tgon::platform::GetAllScreen();

        int n = 3;
    }

    virtual void OnTerminate() override
    {
        int n = 3;
    }

    virtual void OnUpdate() override
    {
        int n = 3;
    }
    virtual void OnDraw() override
    {
        int n = 3;
    }
};

TGON_DECLARE_APPLICATION(ModelJoy)