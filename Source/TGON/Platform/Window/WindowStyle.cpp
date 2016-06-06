#include "PrecompiledHeader.h"
#include "WindowStyle.h"

#include "../../Core/XML/TXMLReader.h"
#include "../MessageBox/TMessageBox.h"


tgon::WindowStyle tgon::WindowStyle::LoadFromXML(
	const wchar_t* xmlPath )
{
	WindowStyle parsedWndStyle;


	TXMLReader xmlReader( xmlPath );
	if ( xmlReader.fail( ))
	{
		TMessageBox::Show( L"Failed to load WindowStyle." );
	}

	for ( const auto& xmlNodeElem : xmlReader )
	{
		if ( !std::wcscmp( xmlNodeElem->GetValue( ), L"Title" ))
		{
			parsedWndStyle.title = static_cast<TXMLElement*>( xmlNodeElem )->
				GetText( );
		}
		else if ( !std::wcscmp( xmlNodeElem->GetValue( ), L"Transform" ))
		{
			parsedWndStyle.x = static_cast<TXMLElement*>( xmlNodeElem )->
				IntAttribute( L"x" );
			parsedWndStyle.y = static_cast<TXMLElement*>( xmlNodeElem )->
				IntAttribute( L"y" );
			parsedWndStyle.width = static_cast<TXMLElement*>( xmlNodeElem )->
				IntAttribute( L"width" );
			parsedWndStyle.height = static_cast<TXMLElement*>( xmlNodeElem )->
				IntAttribute( L"height" );
		}
		else if ( !std::wcscmp( xmlNodeElem->GetValue( ), L"Style" ))
		{
			parsedWndStyle.Popup = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"Popup" );
		}
		else if ( !std::wcscmp( xmlNodeElem->GetValue( ), L"Function" ))
		{
			parsedWndStyle.ClipCursor = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"ClipCursor" );
			parsedWndStyle.EventHandleable = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"EventHandleable" );
			parsedWndStyle.Resizeable = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"Resizeable" );
			parsedWndStyle.Maximized = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"Maximized" );
			parsedWndStyle.Minimized = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"Minimized" );
			parsedWndStyle.ShowTopOnCreated = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"ShowTopOnCreated" );
			parsedWndStyle.ShowMiddle = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"ShowMiddle" );
			parsedWndStyle.TopMost = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"TopMost" );
			parsedWndStyle.ShowImmediately = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"ShowImmediately" );
			parsedWndStyle.SupportWindowTransparency = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"SupportWindowTransparency" );
			parsedWndStyle.SupportPerPixelTransparency = static_cast<TXMLElement*>( xmlNodeElem )->
				BoolAttribute( L"SupportPerPixelTransparency" );
		}
	}

	return parsedWndStyle;
}