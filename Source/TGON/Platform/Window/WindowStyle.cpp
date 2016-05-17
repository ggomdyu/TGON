#include "PrecompiledHeader.h"
#include "WindowStyle.h"

#include "../../Core/XML/TXML.h"


using namespace tinyxml2;


tgon::WindowStyle tgon::WindowStyle::ParseFromXML(
		const wchar_t* const xmlPath )
{
	TiXMLDocument doc;
	if ( doc.LoadFile( xmlPath ) != ::XMLError::XML_NO_ERROR )
	{
		return WindowStyle( );
	}


	XMLElement* root = doc.RootElement();
	WindowStyle wndStyle;

	// Caption
	XMLElement* sibling =
		FindElementFromParent( L"Caption", root );
	wndStyle.caption = sibling->GetText( );

	// Position
	sibling = 
		FindElementFromParent( L"Position", root );
	wndStyle.x = 
		sibling->IntAttribute( L"x" );
	wndStyle.y = 
		sibling->IntAttribute( L"y" );

	// Size
	sibling = 
		FindElementFromParent( L"Size", root );
	wndStyle.width =
		sibling->IntAttribute( L"width" );
	wndStyle.height = 
		sibling->IntAttribute( L"height" );

	// Attribute
	sibling =
		FindElementFromParent( L"Attribute", root );
	wndStyle.Resizeable =
		sibling->BoolAttribute( L"Resizeable" );
	wndStyle.Popup =
		sibling->BoolAttribute( L"Popup" );
	wndStyle.Maximized =
		sibling->BoolAttribute( L"Maximized" );
	wndStyle.Minimized =
		sibling->BoolAttribute( L"Minimized" );
	wndStyle.ShowTopOnCreated =
		sibling->BoolAttribute( L"ShowTopOnCreated" );
	wndStyle.ShowMiddle =
		sibling->BoolAttribute( L"ShowMiddle" );
	wndStyle.TopMost =
		sibling->BoolAttribute( L"TopMost" );
	wndStyle.ShowImmediately =
		sibling->BoolAttribute( L"ShowImmediately" );
	wndStyle.SupportWindowTransparency = 
		sibling->BoolAttribute( L"SupportWindowTransparency" );
	wndStyle.SupportPerPixelTransparency = 
		sibling->BoolAttribute( L"SupportPerPixelTransparency" );
	
	return wndStyle;
}