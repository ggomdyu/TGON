#pragma once
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
#include <Core/Delegate/TDelegate.h>
#include <Core/Object/TObject.h>
#include <Engine/GameApplication.h>

using namespace tgon;

class MyCustomWindow :
    public TWindowFrame
{
public:
    using TWindowFrame::TWindowFrame;

public:
    virtual void OnMouseDown(int32_t x, int32_t y, MouseType mouseType) override
    {
    }

    virtual bool OnDestroy() override
    {
        return MessageBox(NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO) == IDYES;
    }
};

class TGONSample :
    public GameApplication
{
public:
    TGON_MAKE_OBJECT_INTERFACE(TGONSample)

public:
    TGONSample() :
        GameApplication(MakeWindow<TWindowFrame>())
    {
	}

public:
	virtual ~TGONSample( )
	{
	}

public:
	virtual void OnRender( ) override
	{
	}

	virtual void OnUpdate( ) override
	{
	}
};