#include "PrecompiledHeader.h"
#include "WindowStyle.h"


// TODO : FIX BUTTOM-UP REFERENCING
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
			parsedWndStyle.popup = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Popup" );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ), "Function" ))
		{
			parsedWndStyle.resizeable = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Resizeable" );
			parsedWndStyle.maximized = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Maximized" );
			parsedWndStyle.minimized = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Minimized" );
			parsedWndStyle.showTopOnCreated = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowTopOnCreated" );
			parsedWndStyle.showMiddle = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowMiddle" );
			parsedWndStyle.topMost = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "TopMost" );
			parsedWndStyle.showImmediately = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowImmediately" );
			parsedWndStyle.supportWindowTransparency = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportWindowTransparency" );
			parsedWndStyle.supportPerPixelTransparency = static_cast<tinyxml2::XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportPerPixelTransparency" );
		}
	}

	return parsedWndStyle;
}