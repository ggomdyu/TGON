/*
* 작성자 : 차준호
* 작성일 : 2016-04-02
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <stdint.h>
#include <initializer_list>

#include "../Core/TSingleton.h"
#include "../Core/TObject.h"
#include "ISystem.h"


namespace tgon
{


class SystemManager :
	public TObject,
	private TNoncopyable
{
public:
	TGON_OBJECT( SystemManager, TObject )
	TGON_SINGLETON( SystemManager )

	void Update( float tickTime );

public:
	void AddSubSystem( const std::initializer_list<ISystem*>& );
	template <class T> T* GetSubSystem( );

protected:
	SystemManager( );
	virtual ~SystemManager( );

private:
	std::map<uint32_t, ISystem*> m_systemRepo;
};


inline void SystemManager::Update( float tickTime )
{
	for ( auto& sysElem : m_systemRepo )
	{
		sysElem.second->Update( tickTime );
	}
}

inline void SystemManager::AddSubSystem(
	const std::initializer_list<ISystem*>& systemList )
{
	for ( const auto& sysElem : systemList )
	{
		m_systemRepo[sysElem->GetHashCode()] = sysElem;
	}
}

template<class T>
inline T* tgon::SystemManager::GetSubSystem( )
{
	return static_cast<T*>( 
		m_systemRepo[T::GetTypeId().hash_code()] );
}


}