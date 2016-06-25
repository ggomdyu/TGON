#include "PrecompiledHeader.h"
#include "WindowStyle.h"

#include "../MessageBox/TMessageBox.h"
#include "../Core/XML/TXMLReader.h"


const tgon::WindowStyle tgon::WindowStyle::ms_defaultStyle;


tgon::WindowStyle::WindowStyle( )
{
}

tgon::WindowStyle::~WindowStyle( )
{
}

tgon::WindowStyle tgon::WindowStyle::LoadFromXML(
	const char* xmlPath )
{
	// Ready for read a xml.
	TXMLReader xmlReader( xmlPath );
	if ( xmlReader.fail( ))
	{
		std::string errString = "Failed to load WindowStyle. (";
		errString += xmlPath;
		errString += " )";

		TMessageBox::Show( errString.c_str( ));
		return WindowStyle( );
	}

	// Start parsing XML.
	WindowStyle retWndStyle;
	for ( const auto& xmlNodeElem : xmlReader )
	{
		if ( !std::strcmp( xmlNodeElem->Value( ), 
			"Function" ))
		{
			retWndStyle.TopMost = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "TopMost" );
			retWndStyle.FullScreen = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "FullScreen" );
			retWndStyle.Minimized = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Minimized" );
			retWndStyle.Maximized = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Maximized" );
			retWndStyle.Resizeable = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Resizeable" );
			retWndStyle.ClipCursor = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ClipCursor" );
			retWndStyle.EventHandleable = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "EventHandleable" );
			retWndStyle.ShowTopOnCreated = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowTopOnCreated" );
			retWndStyle.ShowMiddle = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowMiddle" );
			retWndStyle.ShowImmediately = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "ShowImmediately" );
			retWndStyle.SupportWindowTransparency = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportWindowTransparency" );
			retWndStyle.SupportPerPixelTransparency = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "SupportPerPixelTransparency" );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ),
			"Transform" ))
		{
			retWndStyle.x = static_cast<XMLElement*>( xmlNodeElem )->
				IntAttribute( "x" );
			retWndStyle.y = static_cast<XMLElement*>( xmlNodeElem )->
				IntAttribute( "y" );
			retWndStyle.width = static_cast<XMLElement*>( xmlNodeElem )->
				IntAttribute( "width" );
			retWndStyle.height = static_cast<XMLElement*>( xmlNodeElem )->
				IntAttribute( "height" );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ),
			"Title" ))
		{
			retWndStyle.title = static_cast<XMLElement*>( xmlNodeElem )->
				GetText( );
		}
		else if ( !std::strcmp( xmlNodeElem->Value( ),
			"Style" ))
		{
			retWndStyle.Popup = static_cast<XMLElement*>( xmlNodeElem )->
				BoolAttribute( "Popup" );
		}
	}

	return retWndStyle;
}