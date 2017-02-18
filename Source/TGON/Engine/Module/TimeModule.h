/**
 * author   ggomdyu
 * since    07/24/2016


 */

#pragma once
#include "Interface/IModule.h"

namespace tgon
{

class TGON_API TimeModule :
	public IModule
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TimeModule )

/**
 * Ctor/Dtor
 */
public:
	TimeModule( );
	virtual ~TimeModule( ) = default;

/**
 * Commands
 */
public:
	virtual void Update( );

/**
 * Gets
 */
	float GetElapsedTime( ) const;

/**
 * Private variables
 */
private:
    uint32_t m_oldTime;
    float m_elapsedTime;
};

} /* namespace tgon */