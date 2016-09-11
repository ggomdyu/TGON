#include "PrecompiledHeader.h"
#include "APlatformWindow.h"

#include "APlatformWindowEventHandler.h"

//////////////////TEMP///////////////////
#include "../Core/XML/TXMLReader.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
/////////////////////////////////////////


namespace tgon
{


decltype( WindowStyle::DefaultStyle ) WindowStyle::DefaultStyle;

WindowStyle WindowStyle::LoadFromXML( const char* xmlPath )
{
	/*using boost::property_tree::ptree;
	ptree pt;
	read_xml( xmlPath, pt );
	std::vector<ptree::value_type> vec;
	for ( const auto& v : pt.get_child( "WindowStyle" )) {vec.push_back( v );}*/

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

APlatformWindow::APlatformWindow( ) :
	m_eventListener( new AWindowEventHandler ),
	m_closed( false )
{
}

APlatformWindow::~APlatformWindow( )
{
	m_closed = true;
}


} /*namespace tgon*/