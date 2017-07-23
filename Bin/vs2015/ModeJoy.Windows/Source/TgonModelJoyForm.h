#pragma once

#if NDEBUG
#   define TGON_DISABLE_CONSOLE
#endif

#include <Core/Platform/Window.h>
#include <Core/Platform/Application.h>
#include <Core/Platform/Time.h>
#include <Core/Platform/TNativeConsole.h>
#include <Core/Utility/AutoCast.h>
#include <Core/Utility/Array.h>
#include <Core/Utility/Enumerator.h>
#include <Core/Utility/Delegate.h>
#include <Core/Random/Random.h>
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>
#include <Core/Math/Point.h>
#include <Core/Object/Object.h>
#include <Core/String/FixedString.h>
#include <Core/String/TEncoding.h>

#include <Engine/GameApplication.h>

using namespace tgon;

#define LOGC(msg, p1) platform::TNativeConsole::Get()->WriteLine(msg, p1);



class CustomWindow :
    public platform::Window
{
public:
    CustomWindow() :
        platform::Window(platform::WindowStyle{})
    {
    }
};

class TGONSample :
    public GameApplication
{
public:
    TGON_MAKE_OBJECT_INTERFACE(TGONSample)

public:
    TGONSample() :
        GameApplication(platform::MakeWindow<platform::Window>(platform::WindowStyle{}))
    {
	}

    virtual ~TGONSample()
    {
	}

public:
    virtual void OnRender() override
    {
	}

    virtual void OnUpdate() override
    {
	}
};
