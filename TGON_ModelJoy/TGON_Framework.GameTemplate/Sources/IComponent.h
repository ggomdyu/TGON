/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-04-26
* ���� ���� :
* ���� ������ :
*/


#pragma once
#include <stdint.h>
#include "IObject.h"


namespace tgon {


class IObject;
class IComponent
{
public:
	IComponent( );
	virtual ~IComponent( ) = 0;

	virtual void Run( float elapsedTime ) = 0;

public:
	void SetOwner( IObject* const owner );
	IObject* GetOwner( );

	template <typename T>
	static uint32_t GetIdentifier( );

private:
	IObject* m_owner;
};


}

#include "IComponent.hpp"