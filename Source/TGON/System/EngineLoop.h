#pragma once
#include <stdint.h>
#include "../Object/TObject.h"
#include "../Window/TWindow.h"


namespace tgon
{


class EngineLoop : public TObject
{
private:
	using TMsgCallback = int32_t(*)( class TWindow*, enum class WindowEvent );

public:
	EngineLoop( const TMsgCallback msgCallback );
	~EngineLoop( );

	void Run( );

private:
	void PreInit( );
	void InitWindow( const TMsgCallback msgCallback );
	void InitGraphicsDevice( );
	void InitManagers( );

private:
	SpTWindow m_window;
	SpTGraphicsDevice m_graphics;
};


}