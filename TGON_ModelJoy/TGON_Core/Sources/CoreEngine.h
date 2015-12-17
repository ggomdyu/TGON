/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-07
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "ISystem.h"
#include "Singleton.h"

#include <vector>
#include <initializer_list>

namespace tgon {
	class CoreEngine
	{
	public:
		Declare_Static_Singleton( CoreEngine )

	public:
		void		Initialize( );
		void		FrameMove( );

	public:
		void		RegisterSystem( const std::initializer_list<ISystem*>& systemList );

		void		Pause( )							{ m_isLoopActivated = false; }
		void		Resume( )						{ m_isLoopActivated = true; }
		void		Exit( )								{ m_isLoopExit = true; }

	private:
		void		FrameMoveAllManagers( float elapsedTime );
		void		FrameMoveAllSystems( float elapsedTime );

	private:
		CoreEngine( );
		~CoreEngine( );

	private:
		bool m_isLoopActivated;
		bool m_isLoopExit;

		std::vector<ISystem*>	m_systemRepo;
	};
}