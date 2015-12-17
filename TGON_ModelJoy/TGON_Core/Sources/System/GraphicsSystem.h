/*
* 작성자 : 차준호
* 작성일 : 2015-12-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "ISystem.h"
#include "Singleton.h"
#include "RTTI.h"

namespace tgon {
	class GraphicsSystem : public ISystem
	{
	public:
		Declare_RTTI( )
		Declare_Static_Singleton( GraphicsSystem )

	public:
		virtual void		Initialize( ) override;
		virtual void		FrameMove( float elapsedTime ) override;

	public:
		virtual void		RecvMessage( _In_ const SociableMessage& msg ) override;

	private:
		GraphicsSystem( );
		virtual ~GraphicsSystem( );

	private:
		
	};
}