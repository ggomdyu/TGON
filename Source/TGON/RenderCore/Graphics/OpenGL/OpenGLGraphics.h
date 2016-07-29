/*
* Author : Cha Junho
* Date : 
* Latest author : 
* Latest date : 
*/


#pragma once
#include "../Abstract/AbstractGraphics.h"


namespace tgon
{


using GraphicsImpl = class OpenGLGraphics;

class TGON_API OpenGLGraphics : 
	public AbstractGraphics
{
protected:
	/*
		Cons/Destructor
	*/
	explicit OpenGLGraphics( class TWindow* deviceWindow );
	
	OpenGLGraphics( const OpenGLGraphics& ) = delete;

	virtual ~OpenGLGraphics( ) = default;

	/*
		Operators
	*/
	OpenGLGraphics& operator=( const OpenGLGraphics& ) = delete;

public:
	/*
		Command
	*/
	// Begin scene rendering. Return true if device can render.
	virtual bool BeginScene( ) override;
	
	// End scene rendering. This function must be called after BeginScene
	virtual bool EndScene( ) override;
	
	// Clear the back buffer scene.
	virtual bool Clear( ) override;

	// Draw the back buffer to visible screen.
	virtual bool Present( ) override;

	//
	virtual void DrawPrimitive( TPrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount ) override;


	/*
		Sets
	*/
	virtual void EnableDepthBuffer( bool isEnable ) override;
	

	/*
		Gets
	*/
	

private:
	/*
		Internal works
	*/


private:
};

inline void tgon::OpenGLGraphics::EnableDepthBuffer( bool isEnable )
{
	if ( isEnable )
	{
		glEnable( GL_DEPTH_TEST );
	}
	else
	{
		glDisable( GL_DEPTH_TEST );
	}
}


}
