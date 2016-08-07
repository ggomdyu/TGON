#include "PrecompiledHeader.h"
#include "TGameBody.h"

#include "../../Engine/Module/InputModule.h"
#include "../../Engine/Module/TimeModule.h"


tgon::TGameBody::TGameBody( const WindowStyle& wndStyle, const GraphicsProperty& graphicsProp ) :
	m_paused( false ),
	m_window( wndStyle )
{
	this->SetupModules( );
}

tgon::TGameBody::~TGameBody( )
{
}

void tgon::TGameBody::FrameUpdate( )
{
	for ( auto module : m_modulesForUpdate )
	{
		module->Update( );
	}
}

void tgon::TGameBody::SetupModules( )
{
	auto AddModule = [this]( const std::shared_ptr<IModule>& module )
	{
		// Check duplication of module
		auto iter = m_modules.find( module->GetHashCode( ));
		if ( iter == m_modules.end( ))
		{
			// If no duplication, Add module
			m_modules.insert({ module->GetHashCode( ), module });
			m_modulesForUpdate.push_back( module );
		}
	};

	AddModule( std::make_shared<TInputModule>( 
		this->GetWindow( ), 
		TInputModule::kMouse | TInputModule::kKeyboard )
	);
}