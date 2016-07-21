#include "PrecompiledHeader.h"
#include "WindowStyle.h"

#include "../../Core/XML/TXMLReader.h"


decltype( tgon::WindowStyle::DefaultStyle ) tgon::WindowStyle::DefaultStyle;


tgon::WindowStyle tgon::WindowStyle::LoadFromXML( const char* xmlPath )
{
	TXMLReader xmlReader( xmlPath );
	if ( xmlReader.Fail( ))
	{
		auto lastError = xmlReader.GetLastError( );
		
		// TODO: Activate TMessageBox
		//TMessageBox::Show( "Failed to load WindowStyle." );
		abort( );
	}

	WindowStyle parsedWndStyle;
	for ( const auto& xmlNodeElem : xmlReader )
	{
		if ( !std::strcmp( xmlNodeElem->Value( ), "Title" ))
		{
			parsedWndStyle.title = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				GetText( );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ), "Transform" ))
		{
			parsedWndStyle.x = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				IntAttribute( "x" );
			parsedWndStyle.y = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				IntAttribute( "y" );
			parsedWndStyle.width = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				IntAttribute( "width" );
			parsedWndStyle.height = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				IntAttribute( "height" );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ), "Style" ))
		{
			parsedWndStyle.Popup = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Popup" );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ), "Function" ))
		{
			parsedWndStyle.Resizeable = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Resizeable" );
			parsedWndStyle.Maximized = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Maximized" );
			parsedWndStyle.Minimized = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Minimized" );
			parsedWndStyle.ShowTopOnCreated = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowTopOnCreated" );
			parsedWndStyle.ShowMiddle = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowMiddle" );
			parsedWndStyle.TopMost = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "TopMost" );
			parsedWndStyle.ShowImmediately = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowImmediately" );
			parsedWndStyle.SupportWindowTransparency = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportWindowTransparency" );
			parsedWndStyle.SupportPerPixelTransparency = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportPerPixelTransparency" );
		}
	}

	return parsedWndStyle;
}