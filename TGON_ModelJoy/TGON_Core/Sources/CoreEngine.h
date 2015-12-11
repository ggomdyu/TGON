#pragma once
#include "ISystem.h"
#include "Singleton.h"

#include <vector>

namespace tgon {
	class CoreEngine
	{
		Implement_Singleton( CoreEngine )

	public:
		void		InitializeAllSystems( );
		void		FrameMoveAllSystems( );

	public:
		void		RegisterSystem( _In_ tgon::ISystem* system )		{ m_systemRepo.push_back( system ); }

	private:
		CoreEngine( );
		~CoreEngine( );

	private:
		std::vector<tgon::ISystem*>	m_systemRepo;
	};
}