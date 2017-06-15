#pragma once

#if NDEBUG
#   define TGON_DISABLE_CONSOLE
#endif

#include <Core/Platform/TWindow.h>
#include <Core/Platform/TApplication.h>
#include <Core/Platform/TTime.h>
#include <Core/Platform/TNativeConsole.h>
#include <Core/Utility/TAutoCast.h>
#include <Core/Utility/TArray.h>
#include <Core/Utility/TEnumerator.h>
#include <Core/Random/TRandom.h>
#include <Core/Math/TMath.h>
#include <Core/Math/TRect.h>
#include <Core/Math/TPoint.h>
#include <Core/Object/TDelegate.h>
#include <Core/Object/TObject.h>
#include <Core/String/TFixedString.h>
#include <Core/String/TEncoding.h>

#include <Engine/GameApplication.h>

using namespace tgon;

#define LOGC(msg, p1) platform::TNativeConsole::Get()->WriteLine(msg, p1);



class CustomWindow :
    public platform::TWindow
{
public:
    CustomWindow() :
        platform::TWindow(platform::TWindowStyle{}, GetModuleHandle(nullptr))
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
        GameApplication(platform::MakeWindow<CustomWindow>())
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
