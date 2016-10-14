#include "PrecompiledHeader.h"
#include "GameApplication.h"


namespace tgon
{


GameApplication::GameApplication( const std::shared_ptr<WindowFrame>& window ) :
	m_paused( false ),
	m_rootWindow( window )
{
}


}