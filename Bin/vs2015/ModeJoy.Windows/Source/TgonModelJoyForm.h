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
#include <Core/Object/ObjectUtility.h>
#include <Core/String/FixedStringUtility.h>
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

class NewObject :
    public tgon::object::Object
{
public:
    TGON_OBJECT(NewObject);
};

class NewObject2 :
    public NewObject
{
public:
    TGON_OBJECT(NewObject2);
};

class NewObject3 :
    public NewObject2
{
public:
    TGON_OBJECT(NewObject3);
};

class NewObject4 :
    public NewObject2
{
public:
    TGON_OBJECT(NewObject4);

    virtual void foo()
    {
        constexpr int n = 32342;
        std::cout << n << std::endl;
        //std::cout << GetDynamicType().GetHashCode() << std::endl;
        //std::cout << SuperType::GetDynamicType().GetHashCode() << std::endl;
    }
};

class TGONSample :
    public GameApplication
{
public:
    TGON_OBJECT(TGONSample)

public:
    TGONSample() :
        GameApplication(platform::MakeWindow<platform::Window>(platform::WindowStyle{}))
    {
        NewObject4* p = new NewObject4;

        constexpr int repeat = 1000000;
        uint64_t begin[3][5];
        uint64_t end[3][5];
        for (int r = 0; r < 5; ++r)
        {
            begin[0][r] = platform::GetOSExecutionTime();
            for (int i = 0; i < repeat; ++i)
            {
                std::cout << tgon::object::DynamicCast<NewObject2>(p);
                std::cout << tgon::object::DynamicCast<NewObject3>(p);
                std::cout << tgon::object::DynamicCast<NewObject4>(p);
            }
            end[0][r] = platform::GetOSExecutionTime();
        }
        for (int r = 0; r < 5; ++r)
        {
            begin[1][r] = platform::GetOSExecutionTime();
            for (int i = 0; i < repeat; ++i)
            {
                std::cout << dynamic_cast<NewObject2*>(p);
                std::cout << dynamic_cast<NewObject3*>(p);
                std::cout << dynamic_cast<NewObject4*>(p);
            }
            end[1][r] = platform::GetOSExecutionTime();
        }
        for (int r = 0; r < 5; ++r)
        {
            begin[2][r] = platform::GetOSExecutionTime();
            for (int i = 0; i < repeat; ++i)
            {
                std::cout << (typeid(NewObject2*).hash_code() == typeid(p).hash_code());
                std::cout << (typeid(NewObject3*).hash_code() == typeid(p).hash_code());
                std::cout << (typeid(NewObject4*).hash_code() == typeid(p).hash_code());
            }
            end[2][r] = platform::GetOSExecutionTime();
        }
        std::wstring str;
        for (int t = 0; t < 3; ++t)
        {
            for (int r = 0; r < 5; ++r)
            {
                str += std::to_wstring(end[t][r] - begin[t][r]);
                str += L"\r\n";
            }
            str += L"/////////////////////////////////////\r\n";
        }
        MessageBox(nullptr, str.c_str(), L"", 0);
        std::cout << "////////////////" << std::endl;

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
