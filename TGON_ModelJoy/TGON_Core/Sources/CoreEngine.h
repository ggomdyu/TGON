#pragma once
#include "ISystem.h"
#include "Singleton.h"

#include <vector>

namespace tgon {
	class CoreEngine
	{
		Implement_Singleton( CoreEngine )

	public:
		void				InitializeAllSystems( );
		void				FrameMove( );

	public:
		void __cdecl		RegisterSystem( _In_ ISystem* system, ... );

	private:
		void				FrameMoveAllManagers( );
		void				FrameMoveAllSystems( );

	private:
		CoreEngine( );
		~CoreEngine( );

	private:
		std::vector<tgon::ISystem*>	m_systemRepo;
	};
}