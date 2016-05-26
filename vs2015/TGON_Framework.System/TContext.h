/*
* Author : Junho-Cha
* Date : 05/18/2015
* Latest author : 
* Latest date : 
*/


#pragma once
#include <System/ISystem.h>
#include <Core/TObject.h>
#include <Config/Build.h>

namespace tgon
{


class TGON_API TContext : public TObject
{
public:
	TGON_OBJECT( TContext, TObject )

	// Register system : Time, ThreadPool, Graphics, Window, ... 
	void RegisterSystem( ISystem* system );
	
	// Get system; Found ISystem pointer will be casted as T*
	template<typename T> T* GetSystem( );

	
public:
	TContext( ) {};
	virtual ~TContext( ) {};

private:
	std::map<uintptr_t, ISystem*> m_systemRepo;
};

inline void tgon::TContext::RegisterSystem( ISystem* system )
{
	m_systemRepo[system->GetHashCode()] = system;
}

template<typename T>
inline T* TContext::GetSystem( )
{
	return static_cast<T*>( m_systemRepo[system->GetHashCode()] );
}


}