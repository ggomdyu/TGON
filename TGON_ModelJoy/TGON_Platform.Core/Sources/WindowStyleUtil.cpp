#include "stdafx.h"
#include "WindowStyleUtil.h"

#include <tglib.h>
#include <XML\TinyXML2Util.h>


#ifdef _MSC_VER
	#pragma warning( disable: 4996 )
#endif


const tgon::WindowStyle tgon::GetWindowStyleFromXML( const char* xmlPath )
{
	WindowStyle wndStyle;

	tinyxml2::XMLDocument doc;
	doc.LoadFile( xmlPath );

	/*
		Parent
	*/
	tinyxml2::XMLElement* root = tinyxml2::FindElementFromRoot( "WindowStyle", doc );

	/*
		Parent's children
	*/
	// Caption
	tinyxml2::XMLElement* sibling = tinyxml2::FindSiblingElementFromParent( "Caption", root );

	wchar_t caption[256] = {0};
	std::mbstowcs( caption, sibling->GetText( ), sizeof( caption ));
	wndStyle.caption = caption;


	// Position
	sibling = tinyxml2::FindSiblingElementFromParent( "Position", root );
	wndStyle.width = std::atoi( sibling->Attribute( "x" ));
	wndStyle.height = std::atoi( sibling->Attribute( "y" ));

	// Size
	sibling = tinyxml2::FindSiblingElementFromParent( "Size", root );
	wndStyle.width = std::atoi( sibling->Attribute( "width" ));
	wndStyle.height = std::atoi( sibling->Attribute( "height" ));

	// Attribute
	sibling = tinyxml2::FindSiblingElementFromParent( "Attribute", root );
	wndStyle.Resizeable = tgon::atob( sibling->Attribute( "Resizeable" ));
	wndStyle.Popup = tgon::atob( sibling->Attribute( "Popup" ));
	wndStyle.Maximized = tgon::atob( sibling->Attribute( "Maximized" ));
	wndStyle.Minimized = tgon::atob( sibling->Attribute( "Minimized" ));
	wndStyle.ShowMiddle = tgon::atob( sibling->Attribute( "ShowMiddle" ));
	wndStyle.TopMost = tgon::atob( sibling->Attribute( "TopMost" ));

	return wndStyle;
}


#ifdef _MSC_VER
	#pragma warning( default: 4996 )
#endif