#pragma once

#if NDEBUG
#   define TGON_DISABLE_CONSOLE
#endif

#include <Core/Platform/Window.h>
#include <Core/Platform/Screen.h>
#include <Core/Platform/Application.h>
#include <Core/Platform/Time.h>
#include <Core/Utility/AutoCast.h>
#include <Core/Utility/Array.h>
#include <Core/Utility/Enumerator.h>
#include <Core/Utility/Delegate.h>
#include <Core/Random/Random.h>
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>
#include <Core/Math/Point.h>
#include <Core/Object/Object.h>
#include <Core/String/FixedStringUtility.h>
#include <Core/String/BuiltinReadOnlyStringUtility.h>
#include <Core/String/TEncoding.h>

#include <Engine/GameApplication.h>

#include <iostream>

using namespace tgon;

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
        auto hashCode = this->GetHashCode();

        int n = 3;
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
