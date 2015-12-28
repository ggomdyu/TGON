/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <System\ISystem.h>
#include <Pattern\Singleton.h>

#include <vector>
#include <initializer_list>

namespace tgon {
	class CoreEngine
	{
	private:
		CoreEngine( );
		~CoreEngine( );

	public:
		Declare_Static_Singleton( CoreEngine )

		void Initialize( );
		void FrameMove( );
	
	public:
		void RegisterSystem( const std::initializer_list<ISystem*>& systemList );
		
		void Pause( );
		void Resume( );
		void Exit( );

	private:
		void UpdateManager( float elapsedTime );
		void UpdateSystem( float elapsedTime );
	
	private:
		bool m_isLoopActivated;
		bool m_isLoopExit;

		std::vector<ISystem*>	m_systemRepo;
	};
}