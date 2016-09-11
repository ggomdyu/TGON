#include "PrecompiledHeader.h"
#include "OpenGLGraphicsDevice.h"

#include "../../../Core/Platform/OSAL/PlatformWindow.h"

#include <gl/GL.h>
#include <gl/GLU.h>


//tgon::OpenGLGraphicsDevice::OpenGLGraphicsDevice( TWindow* deviceWindow, const GraphicsProperty& grpProp ) :
//	AbstractGraphicsDevice( deviceWindow )
//{
//
//}
//
//bool tgon::OpenGLGraphicsDevice::Clear( )
//{
//	// Clear Screen and Depth buffer
//	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//	return true;
//}
//
//bool tgon::OpenGLGraphicsDevice::BeginScene( )
//{
//	glBegin( static_cast<GLenum>( m_drawPrimitiveType ));
//	return true;
//}
//
//bool tgon::OpenGLGraphicsDevice::EndScene( )
//{
//	glEnd( );
//	return true;
//}
//
//bool tgon::OpenGLGraphicsDevice::Present( )
//{
//	return true;
//}
//
//#if BOOST_OS_WINDOWS
//void tgon::OpenGLGraphicsDevice::CreateWin32OpenGL( TWindow* deviceWindow, uint32_t colorDepthBits )
//{
//	// We choose a format that supports OpenGL and double buffering, along with RGBA (red, green, blue, alpha channel).
//	// We try to find a pixel format that matches the bits we decided on (16bit,24bit,32bit).
//
//	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
//	{
//		sizeof( PIXELFORMATDESCRIPTOR ),	// Size Of This Pixel Format Descriptor
//		1,									// Version Number
//		PFD_DRAW_TO_WINDOW |                // Format Must Support Window
//		PFD_SUPPORT_OPENGL |                // Format Must Support OpenGL
//		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
//		PFD_TYPE_RGBA,                      // Request An RGBA Format
//		colorDepthBits,                     // Select Our Color Depth
//		0, 0, 0, 0, 0, 0,                   // Color Bits Ignored
//		0,									// No Alpha Buffer
//		0,									// Shift Bit Ignored
//		0,									// No Accumulation Buffer
//		0, 0, 0, 0,							// Accumulation Bits Ignored
//		16,									// 16Bit Z-Buffer (Depth Buffer)
//		0,									// No Stencil Buffer
//		0,									// No Auxiliary Buffer
//		PFD_MAIN_PLANE,						// Main Drawing Layer
//		0,									// Reserved
//		0, 0, 0                             // Layer Masks Ignored
//	};
//
//	
//	m_dcHandle = GetDC( deviceWindow->GetWindowHandle( ));
//
//	int pixelFormat;
//	pixelFormat = ChoosePixelFormat( m_dcHandle, &pfd );
//
//}
//#endif
//
//void tgon::OpenGLGraphicsDevice::CreateOpenGLInstance( )
//{
//}
