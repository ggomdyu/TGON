/*
* Author : Cha Junho
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include "../../Window/Abstract/AbstractWindowEventHandler.h"
#include <memory>


namespace tgon
{


class TGON_API AbstractWindow : 
	private boost::noncopyable
{
protected:
	/*
		Cons/Destructor
	*/
	AbstractWindow( );

	virtual ~AbstractWindow( ) = 0;


public:
	/*
		Commands
	*/
	virtual bool PumpEvent( ) { return false; }

	virtual void Show( ) {}

	virtual void Hide( ) {}

	virtual void Quit( ) {}

	virtual void Maximize( ) {}

	virtual void Minimize( ) {}

	virtual void BringToTop( ) {}

	virtual void Flash( ) {}

	virtual void EnableGlobalMouseFocus( bool isEnable ) {};


	/*
		Sets
	*/
	void SetEventHandler( const std::shared_ptr<AbstractWindowEventHandler>& eventHandler );

	virtual void SetPosition( int32_t x, int32_t y ) {};

	virtual void SetScale( int32_t width, int32_t height ) {};

	virtual void SetCaption( const wchar_t* src ) {};

	/*
		Gets
	*/
	virtual void GetPosition( int32_t* x, int32_t* y ) const {};

	virtual void GetSize( int32_t* width, int32_t* height ) const {};

	virtual void GetCaption( wchar_t* caption ) const {}

	bool IsEnabledGlobalInputFocus( ) const;

	
protected:
	bool m_isEnabledGlobalMouseFocus;

	std::shared_ptr<AbstractWindowEventHandler> m_eventListener;
};


inline void tgon::AbstractWindow::SetEventHandler( const std::shared_ptr<AbstractWindowEventHandler>& eventListener )
{
	m_eventListener = eventListener;
}

inline bool AbstractWindow::IsEnabledGlobalInputFocus( ) const
{
	return m_isEnabledGlobalMouseFocus;
}


}