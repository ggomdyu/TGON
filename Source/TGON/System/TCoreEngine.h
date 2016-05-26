#pragma once
#include <stdint.h>
#include <vector>

#include "../Core/TObject.h"
#include "../Platform/Slate/PlatformFwd.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TCoreEngine : 
	public TObject
{
public:
	TGON_OBJECT( TCoreEngine, TObject )

public:
	explicit TCoreEngine( );
	~TCoreEngine( );

	void Run( );

private:
	void InitSystem( );
	void InitWindow( );
	void InitGraphics( );

private:
//	SpTWindow m_window;
//	SpTGraphics m_graphics;
};


}