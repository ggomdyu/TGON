#pragma once
#include <Core/Platform/OSAL/PlatformApplication.h>
#include <Core/Platform/OSAL/PlatformTime.h>
#include <Core/Platform/OSAL/PlatformConsole.h>
#include <Core/Template/Cast.h>
#include <Core/Object/Type.h>
#include <Core/Delegate/Delegate.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>


using namespace tgon;


class MyCustomWindow :
	public WindowFrame
{
public:
	using WindowFrame::WindowFrame;

public:
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) override
	{
	}

	virtual bool OnDestroy( ) override
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}
};

//struct E_DESTROY {};
//struct E_CREATE {};
//
//void FooImpl( E_DESTROY, int ) {}
//
//template <typename EvTy, typename... Args>
//void Foo( Args... args )
//{
//	FooImpl( EvTy{}, args... );
//}

class TGONSample :
	public GameApplication
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TGONSample )

private:
    std::shared_ptr<MyCustomWindow> m_myWindow;

public:
	TGONSample( ) :
		GameApplication( MakeWindow<MyCustomWindow>( WindowStyle{} ) )
	{
        m_myWindow = std::static_pointer_cast<MyCustomWindow>( Super::GetRootWindow( ));
	};

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
        HDC hdc = GetDC( m_myWindow->GetWindowHandle( ) );

        auto timeModule = ModuleContext::GetModule<TimeModule>( );

        static float e = 0.0f;
        e += timeModule->GetElapsedTime( );
        auto str = std::to_wstring( e );

        TextOut( hdc, 0, 0, str.c_str( ), str.length( ) );

        ReleaseDC( m_myWindow->GetWindowHandle( ), hdc );
	}
};