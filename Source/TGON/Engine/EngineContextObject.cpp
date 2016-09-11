#include "PrecompiledHeader.h"
#include "EngineContextObject.h"


void tgon::EngineContextObject::AddModule( const std::shared_ptr<IModule>& module )
{
	//std::lock_guard<std::mutex>( this->GetSystemMutex( ));

	// Check duplication of module.
	auto iter = m_modules.find( module->GetHashCode( ));
	if ( iter == m_modules.end( ))
	{
		// If module does not exist in map, then insert to it.
		m_modules.insert({ module->GetHashCode( ), module });

		// Notify module added event to all subscriber.
		this->NotifyEvent<E_MODULEADDED, IModule*>( module.get( ));
	}
	else
	{
		// If module does exist, call assert.
		assert( false && "m_modules already has module you added." );
	}
}