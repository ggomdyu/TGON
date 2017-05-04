#pragma once
#define TGON_ENABLE_CONSOLE

#include <Core/Platform/TApplication.h>
#include <Core/Platform/TTime.h>
#include <Core/Platform/TConsole.h>
#include <Core/Template/TCast.h>
#include <Core/Template/TArray.h>
#include <Core/Template/TEnumerator.h>
#include <Core/Template/TFunctionTraits.h>
#include <Core/Math/TRandom.h>
#include <Core/Math/TMath.h>
#include <Core/Math/TRect.h>
#include <Core/Math/TPoint.h>
#include <Core/Object/TDelegate.h>
#include <Core/Object/TObject.h>
#include <Core/String/TFixedString.h>
#include <Core/String/TEncoding.h>
#include <Engine/GameApplication.h>

using namespace tgon;

class TGONSample :
    public GameApplication
{
public:
    TGON_MAKE_OBJECT_INTERFACE(TGONSample)

public:
    TGONSample() :
        GameApplication(MakeWindow<tgon::window::TWindow>())
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